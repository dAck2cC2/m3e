
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "initrc/initrc.h"
#include "media/NdkMediaCodec.h"
#include "media/NdkMediaExtractor.h"

#include "looper.h"

// for __android_log_print(ANDROID_LOG_INFO, "YourApp", "formatted message");
#include <android/log.h>
#define TAG "NativeCodec"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

typedef struct {
	int fd;
	ANativeWindow* window;
	AMediaExtractor* ex;
	AMediaCodec *codec;
	int64_t renderstart;
	bool sawInputEOS;
	bool sawOutputEOS;
	bool isPlaying;
	bool renderonce;
} workerdata;

workerdata data = { -1, NULL, NULL, NULL, 0, false, false, false, false };

enum {
	kMsgCodecBuffer,
	kMsgPause,
	kMsgResume,
	kMsgPauseAck,
	kMsgDecodeDone,
	kMsgSeek,
};

class mylooper : public looper {
	virtual void handle(int what, void* obj);
};

static mylooper *mlooper = NULL;

int64_t systemnanotime() {
	timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return now.tv_sec * 1000000000LL + now.tv_nsec;
}

void doCodecWork(workerdata *d) {
	ssize_t bufidx = -1;
	if (!d->sawInputEOS) {
		bufidx = AMediaCodec_dequeueInputBuffer(d->codec, 2000);
		if (bufidx >= 0) {
			size_t bufsize;
			auto buf = AMediaCodec_getInputBuffer(d->codec, bufidx, &bufsize);
			auto sampleSize = AMediaExtractor_readSampleData(d->ex, buf, bufsize);
			if (sampleSize < 0) {
				sampleSize = 0;
				d->sawInputEOS = true;
				LOGV("EOS");
			}
			auto presentationTimeUs = AMediaExtractor_getSampleTime(d->ex);

			AMediaCodec_queueInputBuffer(d->codec, bufidx, 0, sampleSize, presentationTimeUs,
				d->sawInputEOS ? AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM : 0);
			AMediaExtractor_advance(d->ex);

		}
		else if (bufidx == AMEDIACODEC_INFO_TRY_AGAIN_LATER) {
			LOGV("no input buffer right now");
		}
		else {
			LOGV("unexpected input ");
		}
	}

	if (!d->sawOutputEOS) {
		AMediaCodecBufferInfo info;
		auto status = AMediaCodec_dequeueOutputBuffer(d->codec, &info, 0);
		if (status >= 0) {
			if (info.flags & AMEDIACODEC_BUFFER_FLAG_END_OF_STREAM) {
				LOGV("output EOS");
				d->sawOutputEOS = true;
			}
			int64_t presentationNano = info.presentationTimeUs * 1000;
			if (d->renderstart < 0) {
				d->renderstart = systemnanotime() - presentationNano;
			}
			static unsigned counter = 0;
			++counter;
			int64_t delay = (d->renderstart + presentationNano) - systemnanotime();
			if (delay > 0) {
				usleep(delay / 1000);
			}
			else {
				LOGE("Delay frame number %u - %lld ns", counter, -delay);
			}
			AMediaCodec_releaseOutputBuffer(d->codec, status, info.size != 0);
			if (d->renderonce) {
				d->renderonce = false;
				return;
			}
		}
		else if (status == AMEDIACODEC_INFO_OUTPUT_BUFFERS_CHANGED) {
			LOGV("output buffers changed");
		}
		else if (status == AMEDIACODEC_INFO_OUTPUT_FORMAT_CHANGED) {
			auto format = AMediaCodec_getOutputFormat(d->codec);
			LOGV("format changed to: %s", AMediaFormat_toString(format));
			AMediaFormat_delete(format);
		}
		else if (status == AMEDIACODEC_INFO_TRY_AGAIN_LATER) {
			LOGV("no output buffer right now");
		}
		else {
			LOGV("unexpected info code: %zd", status);
		}
	}

	if ( /*!d->sawInputEOS ||*/ !d->sawOutputEOS) {
		mlooper->post(kMsgCodecBuffer, d);
	}
}

void mylooper::handle(int what, void* obj) {
	switch (what) {
	case kMsgCodecBuffer:
		doCodecWork((workerdata*)obj);
		break;

	case kMsgDecodeDone:
	{
		workerdata *d = (workerdata*)obj;
		AMediaCodec_stop(d->codec);
		AMediaCodec_delete(d->codec);
		AMediaExtractor_delete(d->ex);
		d->sawInputEOS = true;
		d->sawOutputEOS = true;
	}
	break;

	case kMsgSeek:
	{
		workerdata *d = (workerdata*)obj;
		AMediaExtractor_seekTo(d->ex, 0, AMEDIAEXTRACTOR_SEEK_NEXT_SYNC);
		AMediaCodec_flush(d->codec);
		d->renderstart = -1;
		d->sawInputEOS = false;
		d->sawOutputEOS = false;
		if (!d->isPlaying) {
			d->renderonce = true;
			post(kMsgCodecBuffer, d);
		}
		LOGV("seeked");
	}
	break;

	case kMsgPause:
	{
		workerdata *d = (workerdata*)obj;
		if (d->isPlaying) {
			// flush all outstanding codecbuffer messages with a no-op message
			d->isPlaying = false;
			post(kMsgPauseAck, NULL, true);
		}
	}
	break;

	case kMsgResume:
	{
		workerdata *d = (workerdata*)obj;
		if (!d->isPlaying) {
			d->renderstart = -1;
			d->isPlaying = true;
			post(kMsgCodecBuffer, d);
		}
	}
	break;
	}
}


int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("%s filename\r\n", argv[0]);
		return -1;
	}

	off_t outStart, outLen;
	int fd = -1;
	fd = open(argv[1], 
#ifdef O_BINARY
		O_BINARY |
#endif
		O_RDONLY);
	if (fd < 0) {
		printf("failed to open file: %s [%d]\r\n", argv[1], fd);
		return -2;
	}

	outLen = lseek(fd, 0, SEEK_END);
	(void)lseek(fd, 0, SEEK_SET);

	outStart = 0;

	InitRC_entry(argc, argv);

	data.fd = fd;

	workerdata *d = &data;

	AMediaExtractor *ex = AMediaExtractor_new();
	media_status_t err = AMediaExtractor_setDataSourceFd(ex, d->fd,
		static_cast<off64_t>(outStart),
		static_cast<off64_t>(outLen));
	close(d->fd);
	if (err != AMEDIA_OK) {
		printf("setDataSource error: %d\r\n", err);
		return -3;
	}

	int numtracks = AMediaExtractor_getTrackCount(ex);

	AMediaCodec *codec = NULL;

	printf("input has %d tracks\r\n", numtracks);
	for (int i = 0; i < numtracks; i++) {
		AMediaFormat *format = AMediaExtractor_getTrackFormat(ex, i);
		const char *s = AMediaFormat_toString(format);
		printf("track %d format: %s\r\n", i, s);
		const char *mime;
		if (!AMediaFormat_getString(format, AMEDIAFORMAT_KEY_MIME, &mime)) {
			printf("no mime type\r\n");
			return -4;
		}
		else if (!strncmp(mime, "video/", 6)) {
			// Omitting most error handling for clarity.
			// Production code should check for errors.
			AMediaExtractor_selectTrack(ex, i);
			codec = AMediaCodec_createDecoderByType(mime);
			AMediaCodec_configure(codec, format, d->window, NULL, 0);
			d->ex = ex;
			d->codec = codec;
			d->renderstart = -1;
			d->sawInputEOS = false;
			d->sawOutputEOS = false;
			d->isPlaying = false;
			d->renderonce = true;
			AMediaCodec_start(codec);
		}
		AMediaFormat_delete(format);
	}

	mlooper = new mylooper();
	mlooper->post(kMsgCodecBuffer, d);

	InitRC_run();

	return 0;
}
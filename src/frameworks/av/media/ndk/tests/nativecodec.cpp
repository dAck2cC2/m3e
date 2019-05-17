
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "initrc/initrc.h"
#include "media/NdkMediaCodec.h"
#include "media/NdkMediaExtractor.h"

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

	AMediaExtractor *ex = AMediaExtractor_new();
	media_status_t err = AMediaExtractor_setDataSourceFd(ex, fd,
		static_cast<off64_t>(outStart),
		static_cast<off64_t>(outLen));
	close(fd);
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
		/*
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
		*/
		AMediaFormat_delete(format);
	}



	return 0;
}
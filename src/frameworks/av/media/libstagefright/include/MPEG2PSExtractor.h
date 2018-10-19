/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MPEG2_PS_EXTRACTOR_H_

#define MPEG2_PS_EXTRACTOR_H_

#include <media/stagefright/foundation/ABase.h>
#include <media/stagefright/MediaExtractor.h>
#include <utils/threads.h>
#include <utils/KeyedVector.h>

#if defined(_MSC_VER)
#include "AnotherPacketSource.h"
#include "ESQueue.h"
#include <media/stagefright/MediaSource.h>
#include <media/stagefright/MetaData.h>
#endif

namespace android {

struct ABuffer;
struct AMessage;
struct Track;
class String8;

struct MPEG2PSExtractor : public MediaExtractor {
    MPEG2PSExtractor(const sp<DataSource> &source);

    virtual size_t countTracks();
    virtual sp<IMediaSource> getTrack(size_t index);
    virtual sp<MetaData> getTrackMetaData(size_t index, uint32_t flags);

    virtual sp<MetaData> getMetaData();

    virtual uint32_t flags() const;
    virtual const char * name() { return "MPEG2PSExtractor"; }

protected:
    virtual ~MPEG2PSExtractor();

private:
    struct Track;
    struct WrappedTrack;

    mutable Mutex mLock;
    sp<DataSource> mDataSource;

    off64_t mOffset;
    status_t mFinalResult;
    sp<ABuffer> mBuffer;
    KeyedVector<unsigned, sp<Track> > mTracks;
    bool mScanning;

    bool mProgramStreamMapValid;
    KeyedVector<unsigned, unsigned> mStreamTypeByESID;

    status_t feedMore();

    status_t dequeueChunk();
    ssize_t dequeuePack();
    ssize_t dequeueSystemHeader();
    ssize_t dequeuePES();

    DISALLOW_EVIL_CONSTRUCTORS(MPEG2PSExtractor);
};

#if  defined(_MSC_VER)

struct MPEG2PSExtractor::Track : public MediaSource {
	Track(MPEG2PSExtractor *extractor,
		unsigned stream_id, unsigned stream_type);

	virtual status_t start(MetaData *params);
	virtual status_t stop();
	virtual sp<MetaData> getFormat();

	virtual status_t read(
		MediaBuffer **buffer, const ReadOptions *options);

protected:
	virtual ~Track();

private:
	friend struct MPEG2PSExtractor;

	MPEG2PSExtractor *mExtractor;

	unsigned mStreamID;
	unsigned mStreamType;
	ElementaryStreamQueue *mQueue;
	sp<AnotherPacketSource> mSource;

	status_t appendPESData(
		unsigned PTS_DTS_flags,
		uint64_t PTS, uint64_t DTS,
		const uint8_t *data, size_t size);

	DISALLOW_EVIL_CONSTRUCTORS(Track);
};

#endif // _MSC_VER

bool SniffMPEG2PS(
        const sp<DataSource> &source, String8 *mimeType, float *confidence,
        sp<AMessage> *);

}  // namespace android

#endif  // MPEG2_PS_EXTRACTOR_H_


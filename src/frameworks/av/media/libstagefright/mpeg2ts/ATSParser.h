/*
 * Copyright (C) 2010 The Android Open Source Project
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

#ifndef A_TS_PARSER_H_

#define A_TS_PARSER_H_

#include <sys/types.h>

#include <media/MediaSource.h>
#include <media/stagefright/foundation/ABase.h>
#include <media/stagefright/foundation/AMessage.h>
#include <utils/KeyedVector.h>
#include <utils/Vector.h>
#include <utils/RefBase.h>
#include <vector>

#if defined(_MSC_VER)
#include <android/hardware/cas/native/1.0/IDescrambler.h>
#endif

namespace android {
namespace hardware {
namespace cas {
namespace V1_0 {
struct ICas;
}}}
using hardware::cas::V1_0::ICas;

class ABitReader;
struct ABuffer;
struct AnotherPacketSource;

struct ATSParser : public RefBase {
    enum DiscontinuityType {
        DISCONTINUITY_NONE              = 0,
        DISCONTINUITY_TIME              = 1,
        DISCONTINUITY_AUDIO_FORMAT      = 2,
        DISCONTINUITY_VIDEO_FORMAT      = 4,
        DISCONTINUITY_ABSOLUTE_TIME     = 8,
        DISCONTINUITY_TIME_OFFSET       = 16,

        // For legacy reasons this also implies a time discontinuity.
        DISCONTINUITY_FORMATCHANGE      =
            DISCONTINUITY_AUDIO_FORMAT
                | DISCONTINUITY_VIDEO_FORMAT
                | DISCONTINUITY_TIME,
        DISCONTINUITY_FORMAT_ONLY       =
            DISCONTINUITY_AUDIO_FORMAT
                | DISCONTINUITY_VIDEO_FORMAT,
    };

    enum Flags {
        // The 90kHz clock (PTS/DTS) is absolute, i.e. PTS=0 corresponds to
        // a media time of 0.
        // If this flag is _not_ specified, the first PTS encountered in a
        // program of this stream will be assumed to correspond to media time 0
        // instead.
        TS_TIMESTAMPS_ARE_ABSOLUTE = 1,
        // Video PES packets contain exactly one (aligned) access unit.
        ALIGNED_VIDEO_DATA         = 2,
    };

    enum SourceType {
        VIDEO = 0,
        AUDIO = 1,
        META  = 2,
        NUM_SOURCE_TYPES = 3
    };

    // Event is used to signal sync point event at feedTSPacket().
    struct SyncEvent {
        explicit SyncEvent(off64_t offset);

        void init(off64_t offset, const sp<AnotherPacketSource> &source,
                int64_t timeUs, SourceType type);

        bool hasReturnedData() const { return mHasReturnedData; }
        void reset();
        off64_t getOffset() const { return mOffset; }
        const sp<AnotherPacketSource> &getMediaSource() const { return mMediaSource; }
        int64_t getTimeUs() const { return mTimeUs; }
        SourceType getType() const { return mType; }

    private:
        bool mHasReturnedData;
        /*
         * mHasReturnedData == false: the current offset (or undefined if the returned data
                                      has been invalidated via reset())
         * mHasReturnedData == true: the start offset of sync payload
         */
        off64_t mOffset;
        /* The media source object for this event. */
        sp<AnotherPacketSource> mMediaSource;
        /* The timestamp of the sync frame. */
        int64_t mTimeUs;
        SourceType mType;
    };

    explicit ATSParser(uint32_t flags = 0);

    status_t setMediaCas(const sp<ICas> &cas);

    // Feed a TS packet into the parser. uninitialized event with the start
    // offset of this TS packet goes in, and if the parser detects PES with
    // a sync frame, the event will be initiailzed with the start offset of the
    // PES. Note that the offset of the event can be different from what we fed,
    // as a PES may consist of multiple TS packets.
    //
    // Even in the case feedTSPacket() returns non-OK value, event still may be
    // initialized if the parsing failed after the detection.
    status_t feedTSPacket(
            const void *data, size_t size, SyncEvent *event = NULL);

    void signalDiscontinuity(
            DiscontinuityType type, const sp<AMessage> &extra);

    void signalEOS(status_t finalResult);

    sp<AnotherPacketSource> getSource(SourceType type);
    bool hasSource(SourceType type) const;

    bool PTSTimeDeltaEstablished();

    int64_t getFirstPTSTimeUs();

    void signalNewSampleAesKey(const sp<AMessage> &keyItem);

    enum {
        // From ISO/IEC 13818-1: 2000 (E), Table 2-29
        STREAMTYPE_RESERVED             = 0x00,
        STREAMTYPE_MPEG1_VIDEO          = 0x01,
        STREAMTYPE_MPEG2_VIDEO          = 0x02,
        STREAMTYPE_MPEG1_AUDIO          = 0x03,
        STREAMTYPE_MPEG2_AUDIO          = 0x04,
        STREAMTYPE_MPEG2_AUDIO_ADTS     = 0x0f,
        STREAMTYPE_MPEG4_VIDEO          = 0x10,
        STREAMTYPE_METADATA             = 0x15,
        STREAMTYPE_H264                 = 0x1b,

        // From ATSC A/53 Part 3:2009, 6.7.1
        STREAMTYPE_AC3                  = 0x81,

        // Stream type 0x83 is non-standard,
        // it could be LPCM or TrueHD AC3
        STREAMTYPE_LPCM_AC3             = 0x83,

        //Sample Encrypted types
        STREAMTYPE_H264_ENCRYPTED       = 0xDB,
        STREAMTYPE_AAC_ENCRYPTED        = 0xCF,
        STREAMTYPE_AC3_ENCRYPTED        = 0xC1,
    };

protected:
    virtual ~ATSParser();

private:
    struct Program;
    struct Stream;
    struct PSISection;
    struct CasManager;
    struct CADescriptor {
        int32_t mSystemID;
        unsigned mPID;
        std::vector<uint8_t> mPrivateData;
    };

    sp<CasManager> mCasManager;

    uint32_t mFlags;
    Vector<sp<Program> > mPrograms;

    // Keyed by PID
    KeyedVector<unsigned, sp<PSISection> > mPSISections;

    int64_t mAbsoluteTimeAnchorUs;

    bool mTimeOffsetValid;
    int64_t mTimeOffsetUs;
    int64_t mLastRecoveredPTS;

    size_t mNumTSPacketsParsed;

    sp<AMessage> mSampleAesKeyItem;

    void parseProgramAssociationTable(ABitReader *br);
    void parseProgramMap(ABitReader *br);
    // Parse PES packet where br is pointing to. If the PES contains a sync
    // frame, set event with the time and the start offset of this PES.
    // Note that the method itself does not touch event.
    void parsePES(ABitReader *br, SyncEvent *event);

    // Strip remaining packet headers and pass to appropriate program/stream
    // to parse the payload. If the payload turns out to be PES and contains
    // a sync frame, event shall be set with the time and start offset of the
    // PES.
    // Note that the method itself does not touch event.
    status_t parsePID(
        ABitReader *br, unsigned PID,
        unsigned continuity_counter,
        unsigned payload_unit_start_indicator,
        unsigned transport_scrambling_control,
        unsigned random_access_indicator,
        SyncEvent *event);

    status_t parseAdaptationField(
            ABitReader *br, unsigned PID, unsigned *random_access_indicator);

    // see feedTSPacket().
    status_t parseTS(ABitReader *br, SyncEvent *event);

    void updatePCR(unsigned PID, uint64_t PCR, uint64_t byteOffsetFromStart);

    uint64_t mPCR[2];
    uint64_t mPCRBytes[2];
    int64_t mSystemTimeUs[2];
    size_t mNumPCRs;

    DISALLOW_EVIL_CONSTRUCTORS(ATSParser);
};


#if defined(_MSC_VER) // M3E:

using  hardware::HidlMemory;
struct ElementaryStreamQueue;
using namespace hardware::cas::native::V1_0;

struct ATSParser::Program : public RefBase {
    Program(ATSParser* parser, unsigned programNumber, unsigned programMapPID,
        int64_t lastRecoveredPTS);

    bool parsePSISection(
        unsigned pid, ABitReader* br, status_t* err);

    // Pass to appropriate stream according to pid, and set event if it's a PES
    // with a sync frame.
    // Note that the method itself does not touch event.
    bool parsePID(
        unsigned pid, unsigned continuity_counter,
        unsigned payload_unit_start_indicator,
        unsigned transport_scrambling_control,
        unsigned random_access_indicator,
        ABitReader* br, status_t* err, SyncEvent* event);

    void signalDiscontinuity(
        DiscontinuityType type, const sp<AMessage>& extra);

    void signalEOS(status_t finalResult);

    sp<AnotherPacketSource> getSource(SourceType type);
    bool hasSource(SourceType type) const;

    int64_t convertPTSToTimestamp(uint64_t PTS);

    bool PTSTimeDeltaEstablished() const {
        return mFirstPTSValid;
    }

    unsigned number() const { return mProgramNumber; }

    void updateProgramMapPID(unsigned programMapPID) {
        mProgramMapPID = programMapPID;
    }

    unsigned programMapPID() const {
        return mProgramMapPID;
    }

    uint32_t parserFlags() const {
        return mParser->mFlags;
    }

    sp<CasManager> casManager() const {
        return mParser->mCasManager;
    }

    uint64_t firstPTS() const {
        return mFirstPTS;
    }

    void updateCasSessions();

    void signalNewSampleAesKey(const sp<AMessage>& keyItem);

private:
    struct StreamInfo {
        unsigned mType;
        unsigned mPID;
        int32_t mCASystemId;
    };

    ATSParser* mParser;
    unsigned mProgramNumber;
    unsigned mProgramMapPID;
    KeyedVector<unsigned, sp<Stream> > mStreams;
    bool mFirstPTSValid;
    uint64_t mFirstPTS;
    int64_t mLastRecoveredPTS;
    sp<AMessage> mSampleAesKeyItem;

    status_t parseProgramMap(ABitReader* br);
    int64_t recoverPTS(uint64_t PTS_33bit);
    bool findCADescriptor(
        ABitReader* br, unsigned infoLength, CADescriptor* caDescriptor);
    bool switchPIDs(const Vector<StreamInfo>& infos);

    DISALLOW_EVIL_CONSTRUCTORS(Program);
};

struct ATSParser::Stream : public RefBase {
    Stream(Program* program,
        unsigned elementaryPID,
        unsigned streamType,
        unsigned PCR_PID,
        int32_t CA_system_ID);

    unsigned type() const { return mStreamType; }
    unsigned pid() const { return mElementaryPID; }
    void setPID(unsigned pid) { mElementaryPID = pid; }

    void setCasInfo(
        int32_t systemId,
        const sp<IDescrambler>& descrambler,
        const std::vector<uint8_t>& sessionId);

    // Parse the payload and set event when PES with a sync frame is detected.
    // This method knows when a PES starts; so record mPesStartOffsets in that
    // case.
    status_t parse(
        unsigned continuity_counter,
        unsigned payload_unit_start_indicator,
        unsigned transport_scrambling_control,
        unsigned random_access_indicator,
        ABitReader* br,
        SyncEvent* event);

    void signalDiscontinuity(
        DiscontinuityType type, const sp<AMessage>& extra);

    void signalEOS(status_t finalResult);

    SourceType getSourceType();
    sp<AnotherPacketSource> getSource(SourceType type);

    bool isAudio() const;
    bool isVideo() const;
    bool isMeta() const;

    void signalNewSampleAesKey(const sp<AMessage>& keyItem);

protected:
    virtual ~Stream();

private:
    struct SubSampleInfo {
        size_t subSampleSize;
        unsigned transport_scrambling_mode;
        unsigned random_access_indicator;
    };
    Program* mProgram;
    unsigned mElementaryPID;
    unsigned mStreamType;
    unsigned mPCR_PID;
    int32_t mExpectedContinuityCounter;

    sp<ABuffer> mBuffer;
    sp<AnotherPacketSource> mSource;
    bool mPayloadStarted;
    bool mEOSReached;

    uint64_t mPrevPTS;
    List<off64_t> mPesStartOffsets;

    ElementaryStreamQueue* mQueue;

    bool mScrambled;
    bool mSampleEncrypted;
    sp<AMessage> mSampleAesKeyItem;
    sp<IMemory> mMem;
    sp<MemoryDealer> mDealer;
    sp<HidlMemory> mHidlMemory;
    hardware::cas::native::V1_0::SharedBuffer mDescramblerSrcBuffer;
    sp<ABuffer> mDescrambledBuffer;
    List<SubSampleInfo> mSubSamples;
    sp<IDescrambler> mDescrambler;

    // Flush accumulated payload if necessary --- i.e. at EOS or at the start of
    // another payload. event is set if the flushed payload is PES with a sync
    // frame.
    status_t flush(SyncEvent* event);

    // Flush accumulated payload for scrambled streams if necessary --- i.e. at
    // EOS or at the start of another payload. event is set if the flushed
    // payload is PES with a sync frame.
    status_t flushScrambled(SyncEvent* event);

    // Check if a PES packet is scrambled at PES level.
    uint32_t getPesScramblingControl(ABitReader* br, int32_t* pesOffset);

    // Strip and parse PES headers and pass remaining payload into onPayload
    // with parsed metadata. event is set if the PES contains a sync frame.
    status_t parsePES(ABitReader* br, SyncEvent* event);

    // Feed the payload into mQueue and if a packet is identified, queue it
    // into mSource. If the packet is a sync frame. set event with start offset
    // and timestamp of the packet.
    void onPayloadData(
        unsigned PTS_DTS_flags, uint64_t PTS, uint64_t DTS,
        unsigned PES_scrambling_control,
        const uint8_t* data, size_t size,
        int32_t payloadOffset, SyncEvent* event);

    // Ensure internal buffers can hold specified size, and will re-allocate
    // as needed.
    bool ensureBufferCapacity(size_t size);

    DISALLOW_EVIL_CONSTRUCTORS(Stream);
};

struct ATSParser::PSISection : public RefBase {
    PSISection();

    status_t append(const void* data, size_t size);
    void setSkipBytes(uint8_t skip);
    void clear();

    bool isComplete() const;
    bool isEmpty() const;
    bool isCRCOkay() const;

    const uint8_t* data() const;
    size_t size() const;

protected:
    virtual ~PSISection();

private:
    sp<ABuffer> mBuffer;
    uint8_t mSkipBytes;
    static uint32_t CRC_TABLE[];

    DISALLOW_EVIL_CONSTRUCTORS(PSISection);
};
#endif // _MSC_VER

}  // namespace android

#endif  // A_TS_PARSER_H_

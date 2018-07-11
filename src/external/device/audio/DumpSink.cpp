
//#define LOG_NDEBUG 0
#define LOG_TAG "DumpSink"
#include <utils/ADebugExt.h>
#include <utils/Log.h>
#include <DumpSink.h>

#define DUMP_SINK_FILE "./audio.dump"
#define DUMP_SINK_SIZE (4096)

namespace android {

/******************************************************************************
    DumpSink
******************************************************************************/

DumpSink::DumpSink() :
    mFile(NULL)
{
    AUTO_LOG();
}

DumpSink::~DumpSink()
{
    AUTO_LOG();

    close_l();
}

status_t 
DumpSink::createSink_l()
{
    AUTO_LOG();
    
    if (NULL == mFile) {
        mFile = fopen(DUMP_SINK_FILE, "w");
    }
    CHECK_PTR_EXT(mFile, NO_MEMORY);

    RETURN(OK);
}

status_t    
DumpSink::restoreTrack_l(const char *from)
{
    AUTO_LOG();
    
    RETURN(OK);
}

bool        
DumpSink::isOffloaded_l() const
{
    AUTO_LOG();
    
    return false;
}

uint32_t    
DumpSink::updateAndGetPosition_l()
{
    AUTO_LOG();
    
    return 0;
}

nsecs_t 
DumpSink::processAudioBuffer_l()
{
    AUTO_LOG();

    CHECK_PTR_EXT(mFile, NS_INACTIVE);

    void* buf = malloc(DUMP_SINK_SIZE);
    CHECK_PTR_EXT(buf, NS_INACTIVE);

    size_t nsrc = AudioSinkBase::mCblk(this, buf, DUMP_SINK_SIZE, AudioSinkBase::mCookie, CB_EVENT_FILL_BUFFER);
    if ((nsrc <= 0) || (nsrc > DUMP_SINK_SIZE)) {
        free(buf);
        RETURN(NS_WHENEVER);
    }    

    fwrite(buf, 1, nsrc, mFile);
    free(buf);

    RETURN(0);
}

void        
DumpSink::flush_l()
{
    AUTO_LOG();
}

void
DumpSink::close_l()
{
    AUTO_LOG();

    if (mFile != 0) {
        fclose(mFile);
        mFile = 0;
    }
}

}  // namespace android


//#define LOG_NDEBUG 0
#define LOG_TAG "DumpSink"
#include <utils/ADebugExt.h>
#include <utils/Log.h>
#include <DumpSink.h>

namespace android {

/******************************************************************************
    DumpSink
******************************************************************************/

DumpSink::DumpSink()
{
    AUTO_LOG();
}

DumpSink::~DumpSink()
{
    AUTO_LOG();
}

status_t 
DumpSink::createSink_l()
{
    AUTO_LOG();
    
    return 0;
}

status_t    
DumpSink::restoreTrack_l(const char *from)
{
    AUTO_LOG();
    
    return 0;
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

void        
DumpSink::flush_l()
{
    AUTO_LOG();
    
    return;
}

nsecs_t 
DumpSink::processAudioBuffer_l()
{
    AUTO_LOG();

    return 0;
}


}  // namespace android

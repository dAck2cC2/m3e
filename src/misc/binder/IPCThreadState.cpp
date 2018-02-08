#define LOG_TAG "IPCThreadState"

#include <binder/IPCThreadState.h>

// ---------------------------------------------------------------------------

namespace android {

IPCThreadState* IPCThreadState::self()
{
    return NULL;
}

void IPCThreadState::flushCommands()
{

}

}

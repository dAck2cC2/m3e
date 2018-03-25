
#include "RenderScript.h"

using namespace android;
using namespace RSC;

bool RS::gInitialized = false;
bool RS::usingNative = false;
pthread_mutex_t RS::gInitMutex = PTHREAD_MUTEX_INITIALIZER;
dispatchTable* RS::dispatch = nullptr;

RS::RS() {
}

RS::~RS() {
}

bool RS::init(const char * name, uint32_t flags) {
    return false;
}

bool RS::initDispatch(int targetApi) {
    return false;
}

bool RS::init(const char * name, uint32_t flags, int targetApi) {
    return true;
}

void RS::throwError(RSError error, const char *errMsg) {
}

RSError RS::getError() {
    return mCurrentError;
}


void * RS::threadProc(void *vrsc) {
    return nullptr;
}

void RS::setErrorHandler(ErrorHandlerFunc_t func) {
    mErrorFunc = func;
}

void RS::setMessageHandler(MessageHandlerFunc_t func) {
    mMessageFunc  = func;
}

void RS::finish() {
}


#ifndef __IENGINE_SCANNER_H__
#define __IENGINE_SCANNER_H__

#include "engine/EngineDefine.h"
#include "engine/IEngineScannerClient.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

ENGINE_BEGIN

enum {
    // This file or directory was scanned successfully.
    MEDIA_SCAN_RESULT_OK,
    // This file or directory was skipped because it was not found, could
    // not be opened, was of an unsupported type, or was malfored in some way.
    MEDIA_SCAN_RESULT_SKIPPED,
    // The scan should be aborted due to a fatal error such as out of memory
    // or an exception.
    MEDIA_SCAN_RESULT_ERROR,
};

class IEngineScanner : public RefBase
{
public:
    explicit IEngineScanner() {};
    virtual ~IEngineScanner() {};

    virtual int processFile(
        const char *path, const char *mimeType, const sp<IEngineScannerClient>& client) = 0;

    virtual int processDirectory(
        const char *path, sp<IEngineScannerClient>& client) = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineScanner);
};

ENGINE_END

#endif // __IENGINE_SCANNER_H__


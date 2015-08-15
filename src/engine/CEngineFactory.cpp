/**
 * @file  CEngineFactory.cpp
 * @brief CEngineFactory Class Source File
 * @attention
 */

/*---------------------------------------------------------------------------*/
//    INCLUDE
/*---------------------------------------------------------------------------*/

#include "engine/CEngineFactory.h"
#include "impl/CEngineAnalyzer.h"
#include "impl/CEngineMonitor.h"
#include "impl/CEncoderClient.h"
#include "impl/CEncoderLame.h"
#include "media/CMediaFileScanner.h"

ENGINE_BEGIN
// ---------------------------------------------------------------------------

const char *OPTION_INPUT_FILE         = "option/input/file";
const char *OPTION_INPUT_PATH         = "option/input/path";
const char *OPTION_OUTPUT_PATH        = "option/output/path";
const char *OPTION_OPERATION          = "option/operation";
const char *OPTION_ENCODER_TYPE       = "option/encoder/type";
const char *OPTION_ENCODER_NAME       = "option/encoder/name";
const char *OPTION_REMOVE_SOURCE_FILE = "option/source/remove";

const char *INFO_INPUT_FILE   = "info/input/file";
const char *INFO_OUTPUT_FILE  = "info/outpur/file";
const char *INFO_OPERATION    = "info/operation";
const char *INFO_CORE_COUNT   = "info/core/count";

const char *OPERATION_ENCODE  = "operation/encode";
const char *OPERATION_DECODE  = "operation/decode";

const char *ENCODER_TYPE_MP3  = "encoder/type/mp3";
const char *ENCODER_TYPE_AAC  = "encoder/type/aac";

const char *ENCODER_NAME_LAME = "encoder/name/lame";


ANDROID_SINGLETON_STATIC_INSTANCE(CEngineFactory);

static CEngineMonitor g_cMonitor;

CEngineFactory::CEngineFactory()
{
}

CEngineFactory::~CEngineFactory()
{
}

sp<IEngineAnalyzer>
CEngineFactory::createAnalyzer()
{
    return (new CEngineAnalyzer());
}

sp<IEngineScanner>
CEngineFactory::createScanner()
{
    return (new CMediaFileScanner());
}

sp<IEngineScannerClient>
CEngineFactory::createClient(const char* pszOperation_in)
{
    if (NULL == pszOperation_in) {
        return (NULL);
    }

    if (!strcasecmp(pszOperation_in, OPERATION_ENCODE)) {
        return (new CEncoderClient());
    } else if (!strcasecmp(pszOperation_in, OPERATION_DECODE)) {
        // TO DO
    } else {
        // EMPTY
    }

    return (NULL);
}

sp<IEngineEncoder>
CEngineFactory::createEncoder(const char* pszName_in)
{
    if (NULL == pszName_in) {
        return (NULL);
    }

    if (!strcasecmp(pszName_in, ENCODER_NAME_LAME)) {
        return (new CEncoderLame());
    }

    return (NULL);
}

IEngineMonitor*
CEngineFactory::getMonitor()
{
    return (&g_cMonitor);
}

// ---------------------------------------------------------------------------
ENGINE_END



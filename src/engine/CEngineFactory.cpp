/**
 * @file  CEngineFactory.cpp
 * @brief CEngineFactory Class Source File
 * @attention
 */

/*---------------------------------------------------------------------------*/
//    INCLUDE
/*---------------------------------------------------------------------------*/

#include "engine/CEngineFactory.h"
#include "impl/CEncoderLame.h"
#include "impl/CMP3EncoderClient.h"
#include "media/CMediaFileScanner.h"

ENGINE_BEGIN
// ---------------------------------------------------------------------------

ANDROID_SINGLETON_STATIC_INSTANCE(CEngineFactory);

CEngineFactory::CEngineFactory()
{
}

CEngineFactory::~CEngineFactory()
{
}

sp<IEngineScannerClient>
CEngineFactory::createMP3EncoderClient()
{
    return (new CMP3EncoderClient());
}

sp<IEngineScanner>
CEngineFactory::createMediaScanner()
{
    return (new CMediaFileScanner());
}

sp<IEngineEncoder>
CEngineFactory::createMP3Encoder()
{
    return (new CEncoderLame());
}


// ---------------------------------------------------------------------------
ENGINE_END



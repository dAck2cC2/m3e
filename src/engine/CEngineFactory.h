/*---------------------------------------------------------------------------*/
/**
 * @file  CEngineFactory.h
 * @brief CEngineFactory Class Header File
 * @attention
 */
#ifndef _ENGINE_FACTORY_H_
#define _ENGINE_FACTORY_H_

/*---------------------------------------------------------------------------*/
//    INCLUDE
/*---------------------------------------------------------------------------*/

#include "engine/EngineDefine.h"
#include "engine/IEngineScannerClient.h"
#include "engine/IEngineScanner.h"
#include "engine/IEngineEncoder.h"
#include "utils/Singleton.h"
#include "utils/ABase.h"

ENGINE_BEGIN
// ---------------------------------------------------------------------------

class CEngineFactory : public Singleton<CEngineFactory>
{
    friend class Singleton<CEngineFactory>;

public:
    virtual sp<IEngineScanner>        createMediaScanner();
    virtual sp<IEngineScannerClient>  createMP3EncoderClient();
    virtual sp<IEngineEncoder>        createMP3Encoder();

    virtual ~CEngineFactory();
private:
    explicit CEngineFactory();

    DISALLOW_EVIL_CONSTRUCTORS(CEngineFactory);
};


// ---------------------------------------------------------------------------
ENGINE_END

#endif // _ENGINE_FACTORY_H_


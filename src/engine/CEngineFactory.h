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
#include "engine/IEngineAnalyzer.h"
#include "engine/IEngineMonitor.h"
#include "engine/IEngineEncoder.h"
#include "engine/IEngineScanner.h"
#include "engine/IEngineScannerClient.h"
#include "utils/Singleton.h"
#include "utils/ABase.h"

ENGINE_BEGIN
// ---------------------------------------------------------------------------

class CEngineFactory : public Singleton<CEngineFactory>
{
    friend class Singleton<CEngineFactory>;

public:
    virtual sp<IEngineAnalyzer>       createAnalyzer();
    virtual sp<IEngineScanner>        createScanner();
    virtual sp<IEngineScannerClient>  createClient( const char* pszType_in);
    virtual sp<IEngineEncoder>        createEncoder(const char* pszName_in);

    virtual IEngineMonitor*           getMonitor();

    virtual ~CEngineFactory();
private:
    explicit CEngineFactory();

    DISALLOW_EVIL_CONSTRUCTORS(CEngineFactory);
};


// ---------------------------------------------------------------------------
ENGINE_END

#endif // _ENGINE_FACTORY_H_


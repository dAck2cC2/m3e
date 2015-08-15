/*******************************************************************************
  Created by Jeremy on 2015-08-08.
  Copyright 2015. All rights reserved.
*******************************************************************************/

/*******************************************************************************
    INCLUDE
*******************************************************************************/

#define ENABLE_ADEBUG_EXT
#define LOG_TAG  "main"
#include "utils/ADebugExt.h"
#include "utils/AString.h"
#include "utils/AMessage.h"
#include "engine/CEngineFactory.h"

using namespace ENGINE_NAMESPACE;


/*******************************************************************************
    DEFINITION
*******************************************************************************/

int main(int argc, char *argv[])
{
    sp<IEngineAnalyzer> pAnalyzer = CEngineFactory::getInstance().createAnalyzer();
    CHECK_PTR_EXT(pAnalyzer, UNKNOWN_ERROR);

    int ret = pAnalyzer->parse(argc, argv);
    CHECK_IS_EXT((OK == ret), ret);

    sp<AMessage> pOption = pAnalyzer->getOption();
    CHECK_PTR_EXT(pOption, INVALID_OPERATION);

    AString cOperaton;
    bool chk = pOption->findString(OPTION_OPERATION, &cOperaton);
    CHECK_IS_EXT((true  == chk), UNKNOWN_ERROR);
    CHECK_IS_EXT((false == cOperaton.empty()), UNKNOWN_ERROR);

    sp<IEngineScanner> pScanner = CEngineFactory::getInstance().createScanner();
    CHECK_PTR_EXT(pScanner, UNKNOWN_ERROR);

    sp<IEngineScannerClient> pClient  = CEngineFactory::getInstance().createClient(cOperaton.c_str());
    CHECK_PTR_EXT(pClient, UNKNOWN_ERROR);

    ret = pClient->init(pOption);
    CHECK_IS_EXT((OK == ret), ret);

    AString cSource;
    chk = pOption->findString(OPTION_INPUT_FILE, &cSource);

    if ((true == chk) && (false == cSource.empty())) {
        pScanner->processFile(cSource.c_str(), NULL, pClient);
    }

    chk = pOption->findString(OPTION_INPUT_PATH, &cSource);

    if ((true == chk) && (false == cSource.empty())) {
        pScanner->processDirectory(cSource.c_str(), pClient);
    }

    RETURN(OK);
}


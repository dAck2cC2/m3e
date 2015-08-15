
//#define ENABLE_ADEBUG_EXT
#define LOG_TAG  "CEngineAnalyzer"
#include "utils/ADebugExt.h"
#include "utils/AString.h"
#include "utils/AMessage.h"
//#include "utils/String8.h"
#include "engine/EngineDefine.h"
#include "impl/CEngineAnalyzer.h"

ENGINE_BEGIN

CEngineAnalyzer::CEngineAnalyzer()
    : m_pData(NULL)
{
    AUTO_LOG();
}

CEngineAnalyzer::~CEngineAnalyzer()
{
    AUTO_LOG();
}

int
CEngineAnalyzer::parse(int argc, char *argv[])
{
    AUTO_LOG();

    if ((argc != 2) || (argv[1] == NULL)) {
        usage();
        RETURN (-1);
    }

    //if (m_pData != NULL) {
    //	RETURN(ALREADY_EXISTS);
    //}

    m_pData = new AMessage();
    CHECK_PTR_EXT(m_pData, NO_MEMORY);

    //TO DO

    // only support wav -> mp3
    m_pData->setString(OPTION_OPERATION, OPERATION_ENCODE);
    m_pData->setString(OPTION_ENCODER_TYPE, ENCODER_TYPE_MP3);

    // only support lame
    m_pData->setString(OPTION_ENCODER_NAME, ENCODER_NAME_LAME);

    // only support path
    m_pData->setString(OPTION_INPUT_PATH, argv[1]);

    // only support delete source file
    m_pData->setInt32(OPTION_REMOVE_SOURCE_FILE, 1);

    RETURN(OK);
}

sp<AMessage>
CEngineAnalyzer::getOption()
{
    AUTO_LOG();

    return (m_pData);
}


void
CEngineAnalyzer::usage()
{
    AUTO_LOG();

    printf("usage: m3e file \n");
    printf("file - is a wave file or a path for wave file \n");
}

ENGINE_END


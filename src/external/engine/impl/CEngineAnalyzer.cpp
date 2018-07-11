
#define ENABLE_ADEBUG_EXT
#define LOG_TAG  "CEngineAnalyzer"
#include "utils/ADebugExt.h"
//#include "utils/String8.h"
#include "media/stagefright/foundation/AString.h"
#include "media/stagefright/foundation/AMessage.h"

#include "CEngineAnalyzer.h"

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

void
CEngineAnalyzer::usage()
{
    AUTO_LOG();
    
    printf(
    "usage: m3e [option] <file/path> \n"
    "[option] \n"
    "-e:    encoder the wave file. \n"
    "-p:    play the wave file. \n"
    "<file/path> \n"
    "a file or path for wave file. \n"
    );
}

int
CEngineAnalyzer::parse(int argc, char *argv[])
{
    AUTO_LOG();

    bool valid = false;

    // Is it no need to do this ?
    //if (m_pData != NULL) {
    //	RETURN(ALREADY_EXISTS);
    //}

    m_pData = new AMessage();
    CHECK_PTR_EXT(m_pData, NO_MEMORY);

    for (int i = 1; i < argc; ++i) {
        char* token = argv[i];

        // [option]
        if (*token++ == '-') {
            // -e 
            if (!strcmp(token, "e")) {
                if (i+1 >= argc) {
                    break;
                }

                printf("encode -> %s \n", argv[i+1]);

                // only support path
                m_pData->setString(OPTION_INPUT_PATH, argv[i+1]);

                // only support wav -> mp3
                m_pData->setString(OPTION_OPERATION, OPERATION_ENCODE);
                m_pData->setString(OPTION_ENCODER_TYPE, ENCODER_TYPE_MP3);

                // only support lame
                m_pData->setString(OPTION_ENCODER_NAME, ENCODER_NAME_LAME);

                // only support delete source file
                m_pData->setInt32(OPTION_REMOVE_SOURCE_FILE, 1);
            }
            // -p
            else if (!strcmp(token, "p")) {
                if (i+1 >= argc) {
                    break;
                }
                
                printf("play -> %s \n", argv[i+1]);

                // only support file
                m_pData->setString(OPTION_INPUT_FILE, argv[i+1]);
                
                m_pData->setString(OPTION_OPERATION, OPERATION_PLAYER);
            } 
            else {
                valid = false;
                break;
            }

            valid = true;
        }
    }

    if (!valid) {
        usage();
        RETURN(INVALID_OPERATION);
    }

    RETURN(OK);
}

sp<AMessage>
CEngineAnalyzer::getOption()
{
    AUTO_LOG();

    return (m_pData);
}

ENGINE_END

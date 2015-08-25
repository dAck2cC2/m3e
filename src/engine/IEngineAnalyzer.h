
#ifndef __IENGINE_ANALYZER_H__
#define __IENGINE_ANALYZER_H__

#include "engine/EngineDefine.h"
#include "utils/RefBase.h"
#include "utils/ABase.h"

ENGINE_BEGIN

extern const char *OPTION_INPUT_FILE;
extern const char *OPTION_INPUT_PATH;
extern const char *OPTION_OUTPUT_PATH;
extern const char *OPTION_OPERATION;
extern const char *OPTION_ENCODER_TYPE;
extern const char *OPTION_ENCODER_NAME;
extern const char *OPTION_REMOVE_SOURCE_FILE;

extern const char *OPERATION_ENCODE;
extern const char *OPERATION_DECODE;

extern const char *ENCODER_TYPE_MP3;
extern const char *ENCODER_TYPE_AAC;

extern const char *ENCODER_NAME_LAME;

struct AMessage;

class IEngineAnalyzer : public RefBase
{
public:
    explicit IEngineAnalyzer() {};
    virtual ~IEngineAnalyzer() {};

    virtual int           parse(int argc, char *argv[]) = 0;
    virtual sp<AMessage>  getOption() = 0;

    DISALLOW_EVIL_CONSTRUCTORS(IEngineAnalyzer);
};

ENGINE_END

#endif // __IENGINE_ANALYZER_H__


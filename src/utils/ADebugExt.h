/*---------------------------------------------------------------------------*/
/**
 * @file       ADebugExt.h
 * @brief      Provide log tools
 * @attention  Jeremy Feng All Right Received.
 */
/*---------------------------------------------------------------------------*/
#ifndef __ADEBUG_EXT_H__
#define __ADEBUG_EXT_H__

/*---------------------------------------------------------------------------*/
//    COMPILER SWITCH
/*---------------------------------------------------------------------------*/

#define _SW_ADEBUG_EXT_OFF   0
#define _SW_ADEBUG_EXT_ON    1


#ifdef    ENABLE_ADEBUG_EXT
#define   _SW_ADEBUG_EXT    _SW_ADEBUG_EXT_ON
#else  // ENABLE_ADEBUG_EXT
#define   _SW_ADEBUG_EXT    _SW_ADEBUG_EXT_OFF
#endif // ENABLE_ADEBUG_EXT

/*---------------------------------------------------------------------------*/
//    INCLUDE
/*---------------------------------------------------------------------------*/

#ifndef LOG_TAG
#define LOG_TAG    __FILE__
#endif  // LOG_TAG

#include "utils/UtilsDefine.h"
#include "utils/log.h"
#include "utils/Errors.h"

#ifdef ENABLE_CUSTOMISE

#if   (_SW_ADEBUG_EXT_ON == _SW_ADEBUG_EXT)
#include "utils/ABase.h"
#endif // _SW_ADEBUG_EXT_ON

/*---------------------------------------------------------------------------*/
//    UTILITY MACRO
/*---------------------------------------------------------------------------*/

#define _IS_VALID_PTR(ptr)        ((ptr) != 0)

#if   (_SW_ADEBUG_EXT_ON == _SW_ADEBUG_EXT)
#define AUTO_LOG()                 CAutoLog  autoLog(LOG_TAG, __FUNCTION__)
#define CHECK_PTR(ptr)             if (!_IS_VALID_PTR(ptr)) {ALOGD("[ERROR][%s][%d]ptr is invalid !", __FILE__, __LINE__); return;}
#define CHECK_PTR_EXT(ptr, err)    if (!_IS_VALID_PTR(ptr)) {ALOGD("[ERROR][%s][%d]ptr is invalid !", __FILE__, __LINE__); return (err);}
#define CHECK_IS(cond)             if (!(cond)) {ALOGD("[ERROR][%s][%d]Check is failed !", __FILE__, __LINE__); return;}
#define CHECK_IS_EXT(cond, err)    if (!(cond)) {ALOGD("[ERROR][%s][%d]Check is failed !", __FILE__, __LINE__); return (err);}
#define RETURN(ret)                { if (OK != (ret)) ALOGD("[ERROR][%s][%d]err=%d",__FILE__,__LINE__,(ret)); return (ret);}
#else  // _SW_ADEBUG_EXT_ON
#define AUTO_LOG()
#define CHECK_PTR(ptr)             if (!_IS_VALID_PTR(ptr)) {return;}
#define CHECK_PTR_EXT(ptr, err)    if (!_IS_VALID_PTR(ptr)) {return (err);}
#define CHECK_IS(cond)             if (!(cond)) {return;}
#define CHECK_IS_EXT(cond, err)    if (!(cond)) {return (err);}
#define RETURN(ret)                return (ret)
#endif // _SW_ADEBUG_EXT_ON

/*---------------------------------------------------------------------------*/
//    UTILITY CLASS
/*---------------------------------------------------------------------------*/

#if   (_SW_ADEBUG_EXT_ON == _SW_ADEBUG_EXT)

_UTILS_BEGIN

class CAutoLog
{
public:
    explicit CAutoLog(const char* pszTagName_in, const char* pszApiName_in)
        : m_pszTagName(pszTagName_in), m_pszApiName(pszApiName_in)
    {
        __android_log_print_tag_id(0, 0, m_pszTagName, "[%s][START]", m_pszApiName);
    };

    virtual ~CAutoLog()
    {
        __android_log_print_tag_id(0, 0, m_pszTagName, "[%s][E N D]", m_pszApiName);
    };

private:
    const char* m_pszTagName;
    const char* m_pszApiName;

    DISALLOW_EVIL_CONSTRUCTORS(CAutoLog);
};

_UTILS_END

#endif // _SW_ADEBUG_EXT_ON

#endif // ENABLE_CUSTOMISE

#endif // __ADEBUG_EXT_H__



#include "utils/UtilsDefine.h"
#include "utils/Log.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#define LOG_BUF_SIZE    1024

#ifdef LOG_FILE_NAME
static FILE* s_pLogFile = 0;
#endif // LOG_FILE_NAME


int __android_log_init()
{
#ifdef LOG_FILE_NAME

    if (s_pLogFile != 0) {
        return (-1);
    }

    s_pLogFile = fopen(LOG_FILE_NAME, "w");

    if (s_pLogFile == 0) {
        return (-2);
    }

#endif // LOG_FILE_NAME
    return 0;
}

int __android_log_exit()
{
#ifdef LOG_FILE_NAME

    if (s_pLogFile != 0) {
        fclose(s_pLogFile);
        s_pLogFile = 0;
    }

#endif // LOG_FILE_NAME
    return 0;
}

int __android_log_print_tag_id(int prio, int tagId, const char *tag,  const char *fmt, ...)
{
#ifdef LOG_FILE_NAME
    va_list ap;
    char buf[LOG_BUF_SIZE];

    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);
    va_end(ap);

    __android_log_write(prio, tag, buf);
#endif // LOG_FILE_NAME
    return (0);
}

void __android_log_assert(const char *cond, const char *tag,
                          const char *fmt, ...)
{
    char buf[LOG_BUF_SIZE];

    if (fmt) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);
        va_end(ap);
    } else {
        /* Msg not provided, log condition.  N.B. Do not use cond directly as
         * format string as it could contain spurious '%' syntax (e.g.
         * "%d" in "blocks%devs == 0").
         */
        if (cond) {
            snprintf(buf, LOG_BUF_SIZE, "Assertion failed: %s", cond);
        } else {
            strcpy(buf, "Unspecified assertion failed");
        }
    }

    printf("%s", buf);

#ifdef LOG_FILE_NAME
    __android_log_write(0, tag, buf);
    __android_log_exit();
#endif // LOG_FILE_NAME

#ifdef DEBUG
    assert(0);
#endif // DEBUG
}

int __android_log_write(int prio, const char *tag, const char *text)
{
#ifdef LOG_FILE_NAME
    bool   bNeedCR = false;
    size_t lenTag  = 0;
    size_t lenText = 0;

    if (s_pLogFile == 0) {
        return (-1);
    }

    if (tag != 0) {
        lenTag = strlen(tag);

        if (lenTag > 0) {
            fwrite("[", 1, 1, s_pLogFile);
            fwrite(tag, 1, strlen(tag), s_pLogFile);
            fwrite("]", 1, 1, s_pLogFile);
        }
    }

    if (text != 0) {
        lenText = strlen(text);

        if (lenText > 0) {
            fwrite(text, 1, strlen(text), s_pLogFile);
        }

        if (//(text[lenText - 1] != '\r') ||
            (text[lenText - 1] != '\n')) {
            bNeedCR = true;
        }
    }

    if (bNeedCR) {
        fwrite("\n", 1, 1, s_pLogFile);
    }

#endif // LOG_FILE_NAME	

    return (0);
}


/**
 * \copyright 
 * 
 * \file write_log.c
 * \author xiaoke
 * \version 0.1
 * \date 2020-11-23
 * 
 * \brief 日志调试接口实现
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "write_log.h"


static FILE *logf = NULL;                           /** 日志文件描述符 */
static debug_level_em debug_level = PROXY_WARNING;  /** 日志文件级别，默认warning */

static const char *error_strs[PROXY_MAX] = {
    "[Error]",
    "[Warning]",
    "[Info]",
    "[Debug]"
};

void debug_level_set(debug_level_em level)
{
    debug_level = level;
}

void debug_output(debug_level_em type, const char *file, int lineno, const char *fmt, ...)
{
    if (type > debug_level)
        return;

    if (!fmt)
        return;

    if (!file)
        file = "no_src.c";

    char msg[MAX_DEBUG_MSG_SIZE] = {0};
    snprintf(msg, MAX_DEBUG_MSG_SIZE, "%8s[%15s:%5d]>>>> ", error_strs[type], file, lineno);
    int idx = strlen(msg);

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(&msg[idx], MAX_DEBUG_MSG_SIZE - idx, fmt, ap);
    va_end(ap);

    if (logf != NULL) {
        /** TODO:写入调试文件，控制文件大小 */
        fprintf(logf, msg, strlen(msg));
    } else {
        printf("%s\n", msg);
    }
    return ;
}


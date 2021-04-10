/**
 * \copyright 
 * 
 * \file debug.h
 * \author xiaoke
 * \version 0.1
 * \date 2020-11-23
 * 
 * \brief 打印调试信息相关接口
 */

#ifndef __WRITE_LOG_H__
#define __WRITE_LOG_H__
#include <stdio.h>

#define     MAX_DEBUG_MSG_SIZE      65535    /** 单条调试信息的最大长度 */

typedef enum
{
    PROXY_ERROR = 0,
    PROXY_WARNING,
    PROXY_INFO,
    PROXY_DEBUG,

    PROXY_MAX
} debug_level_em;

/**
 * \brief 设置日志级别
 * 
 * \param [in]	level 日志级别
 */
void debug_level_set(debug_level_em level);

void debug_output(debug_level_em type, const char *file, int lineno, const char *fmt, ...);

/**
* @调试日志
*/
#undef LOGDEBUG
#define LOGDEBUG(level, fmt, ...) do { \
            debug_output(level,  __FILE__, __LINE__, fmt "\n", ##__VA_ARGS__); \
            fflush(stdout); \
        } while(0)

#ifndef UNLOGDEBUG
#define write_log  LOGDEBUG
#else
#define write_log
#endif



#endif
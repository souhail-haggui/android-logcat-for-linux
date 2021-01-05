/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ANDROID_CUTILS_LOGD_H
#define _ANDROID_CUTILS_LOGD_H

/* the stable/frozen log-related definitions have been
 * moved to this header, which is exposed by the NDK
 */
//#include <android/log.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Android log priority values, in ascending priority order.
 */
typedef enum android_LogPriority {
    ANDROID_LOG_UNKNOWN = 0,
    ANDROID_LOG_DEFAULT,    /* only for SetMinPriority() */
    ANDROID_LOG_VERBOSE,
    ANDROID_LOG_DEBUG,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL,
    ANDROID_LOG_SILENT,     /* only for SetMinPriority(); must be last */
} android_LogPriority;

/*
 * Send a simple string to the log.
 */
int __android_log_write(int prio, const char *tag, const char *text);

/*
 * Send a formatted string to the log, used like printf(fmt,...)
 */
int __android_log_print(int prio, const char *tag,  const char *fmt, ...)
#if defined(__GNUC__)
    __attribute__ ((format(printf, 3, 4)))
#endif
    ;

/*
 * A variant of __android_log_print() that takes a va_list to list
 * additional parameters.
 */
int __android_log_vprint(int prio, const char *tag,
                         const char *fmt, va_list ap);

/*
 * Log an assertion failure and SIGTRAP the process to have a chance
 * to inspect it, if a debugger is attached. This uses the FATAL priority.
 */
void __android_log_assert(const char *cond, const char *tag,
			  const char *fmt, ...)    
#if defined(__GNUC__)
    __attribute__ ((noreturn))
    __attribute__ ((format(printf, 3, 4)))
#endif
    ;

#ifdef __cplusplus
}
#endif

/* the rest is only used internally by the system */
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#ifdef HAVE_PTHREADS
#include <pthread.h>
#endif
#include <log/uio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int __android_log_bwrite(int32_t tag, const void *payload, size_t len);
int __android_log_btwrite(int32_t tag, char type, const void *payload,
    size_t len);
int __android_log_bswrite(int32_t tag, const char *payload);

#ifdef __cplusplus
}
#endif

#endif /* _LOGD_H */

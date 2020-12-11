# Android CMD gtest

gtest单元测试so库

## 参考文档

* [0168_gtest.md](0168_gtest.md)
* [0170_Android_cc-test.md](0170_Android_cc-test.md)
* system/core/libsync

## log

### log头文件

* 加入头文件方法：`#include <log/log.h>`
* TAG及ALOGV使用注意事项：`system/core/include/log/log.h`
  ```c
  /*
   * Normally we strip ALOGV (VERBOSE messages) from release builds.
   * You can modify this (for example with "#define LOG_NDEBUG 0"
   * at the top of your source file) to change that behavior.
   */
  #ifndef LOG_NDEBUG
  #ifdef NDEBUG
  #define LOG_NDEBUG 1
  #else
  #define LOG_NDEBUG 0
  #endif
  #endif
  
  /*
   * This is the local tag used for the following simplified
   * logging macros.  You can change this preprocessor definition
   * before using the other macros to change the tag.
   */
  #ifndef LOG_TAG
  #define LOG_TAG NULL
  #endif
  ```
  * 在引用`#include <log/log.h>`之前，先定义宏`LOG_TAG`;
  * 想要看`ALOGV`输出信息，在文件头处，先定义宏`#define LOG_NDEBUG 0`;
* 使用方法：https://android.googlesource.com/platform/system/core/+/4a6e5a3/liblog/README

### ALOGD分析

通过`system/core/include/log/log.h`查看ALOGD宏处理流程

```c
/*
 * ===========================================================================
 *
 * The stuff in the rest of this file should not be used directly.
 */

#define android_printLog(prio, tag, fmt...) \
    __android_log_print(prio, tag, fmt)

/*
 * Basic log message macro.
 *
 * Example:
 *  ALOG(LOG_WARN, NULL, "Failed with error %d", errno);
 *
 * The second argument may be NULL or "" to indicate the "global" tag.
 */
#ifndef ALOG
#define ALOG(priority, tag, ...) \
    LOG_PRI(ANDROID_##priority, tag, __VA_ARGS__)
#endif

/*
 * Log macro that allows you to specify a number for the priority.
 */
#ifndef LOG_PRI
#define LOG_PRI(priority, tag, ...) \
    android_printLog(priority, tag, __VA_ARGS__)
#endif

/*
 * Simplified macro to send a debug log message using the current LOG_TAG.
 */
#ifndef ALOGD
#define ALOGD(...) ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif
```

其中`system/core/lude/android/log.h`定义了`ANDROID_LOG_DEBUG`

```c
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
```

## gtest

### source

https://github.com/ZengjfOS/RaspberryPi/tree/android_gtest

### logcat

```logcat
C:\Users\zengjianfeng\Desktop>adb logcat -s zengjf
--------- beginning of main
--------- beginning of system
12-31 20:36:06.661  8645  8645 D zengjf  : just check for run test
12-31 20:36:06.661  8645  8645 W zengjf  : just check for ALOGW
```

### shell

```shell
root@zengjf:/ # zengjf_test
just check for run test
root@zengjf:/ # zengjf-unit-tests
Running main() from gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from zengjf_test
[ RUN      ] zengjf_test.test
just check for run test
[       OK ] zengjf_test.test (1 ms)
[----------] 1 test from zengjf_test (2 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (2 ms total)
[  PASSED  ] 1 test.
```

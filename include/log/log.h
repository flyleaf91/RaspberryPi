/*
 * Copyright (C) 2005 The Android Open Source Project
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

#include <assert.h>
#include <stdio.h>

#define DEBUG 1

#if DEBUG == 1

#define ALOGE(...)
#define ALOGD(...)
#define ALOG(...)
#define ALOGW(...)
#define ALOG_ASSERT(cond, ...)
#define LOG_ALWAYS_FATAL_IF(cond, ...)
#define LOG_ALWAYS_FATAL(...)

#elif DEBUG == 2

#define ALOGE(...)                  printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOGD(...)                  printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOG(...)                   printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOGW(...)                  printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOG_ASSERT(cond, ...)              if (!cond) { \
                                                printf(__VA_ARGS__); \
                                                printf("\n"); \
                                                assert(cond); \
                                            }

#define LOG_ALWAYS_FATAL_IF(cond, ...)      if (!cond) { \
                                                printf(__VA_ARGS__); \
                                                printf("\n"); \
                                                assert(cond); \
                                            }
#define LOG_ALWAYS_FATAL(...)                printf(__VA_ARGS__); \
                                                printf("\n"); \
                                                assert(false);

#elif DEBUG == 3

#define ALOGE(...)                  printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOGD(...)                  printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOG(...)                   printf(__VA_ARGS__); \
                                        printf("\n");
#define ALOGW(...)                  printf(__VA_ARGS__); \
                                        printf("\n");

#define ALOG_ASSERT(cond, ...)              if (!cond) { \
                                                printf(__VA_ARGS__); \
                                                printf("\n"); \
                                            }

#define LOG_ALWAYS_FATAL_IF(cond, ...)      if (!cond) { \
                                                printf(__VA_ARGS__); \
                                                printf("\n"); \
                                            }

#define LOG_ALWAYS_FATAL(...)               { printf(__VA_ARGS__); \
                                                printf("\n"); \
                                            }

#endif


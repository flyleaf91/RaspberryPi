LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CLANG := true

LOCAL_MODULE := zengjf-unit-tests

LOCAL_CFLAGS += -g -Wall -Werror -std=gnu++11 -Wno-missing-field-initializers -Wno-sign-compare -Wno-writable-strings

LOCAL_SHARED_LIBRARIES += liblog
LOCAL_STATIC_LIBRARIES += libgtest_main

LOCAL_C_INCLUDES += \
	$(TOPDIR)system/core/include/

LOCAL_SRC_FILES := \
	zengjf_test.cpp

include $(BUILD_NATIVE_TEST)

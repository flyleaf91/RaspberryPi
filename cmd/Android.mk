LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES += \
        $(TOPDIR)system/core/include/

LOCAL_SRC_FILES := zengjf_test.c

LOCAL_MODULE := zengjf_test

LOCAL_MODULE_TAGS := optional tests

LOCAL_SHARED_LIBRARIES := liblog

LOCAL_CFLAGS := -Werror

include $(BUILD_EXECUTABLE)


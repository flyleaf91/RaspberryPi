#define LOG_NDEBUG 0

#include <gtest/gtest.h>

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LOG_TAG "zengjf"
#include <log/log.h>

TEST(zengjf_test, test) {
	printf("just check for run test\n");
	ALOGD("just check for run test\n");
	ALOGW("just check for ALOGW\n");
}


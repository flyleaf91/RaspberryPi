#define LOG_NDEBUG 0

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LOG_TAG "zengjf"
#include <log/log.h>

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    printf("just check for run test\n");
    ALOGD("just check for run test\n");
    ALOGW("just check for ALOGW\n");

    return 0;
}

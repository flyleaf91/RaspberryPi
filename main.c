#include <stdio.h>

#define eng             0
#define userdebug       1
#define user            2

int main(int argc, char** argv) {
#if TARGET_BUILD_VARIANT == eng
    printf("eng\n");
#elif TARGET_BUILD_VARIANT == userdebug
    printf("userdebug\n");
#else
    printf("user\n");
#endif
}

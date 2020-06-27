#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long long getMicrosecond() {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    
    return (long long)tv.tv_sec * 1000000 + tv.tv_usec;
}

long long getSecond() {
    return getMicrosecond() / 1000000;
}

long long getMillisecond() {
    return getMicrosecond() / 1000;
}

#if 0
int main()
{
    
    long long start_time = getMicrosecond();
    
    printf("---------------------sleep 3 second-------------------\n");
    sleep(3);
    
    long long end_time = getMicrosecond();

    printf("diff microsecond: %lld\n", end_time - start_time);

    return 0;
}
#endif

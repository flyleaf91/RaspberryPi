# Write a Sort

以前确实没怎么关注算法，学习一下算法，列一下写一个算法的基本架构

## 获取时间

比较算法哪个更好时，同样的输入消耗的时间对比

```C
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

int main()
{

    long long start_time = getMicrosecond();

    printf("---------------------sleep 3 second-------------------\n");
    sleep(3);

    long long end_time = getMicrosecond();

    printf("diff microsecond: %lld\n", end_time - start_time);

    return 0;
}
```

## 测试集

* 这部分很重要，以前看算法书写算法，都是自己写一个数组，但数据量太小没什么意义，所以最好是计算机自己生成会比较合适；
* 每台机器的主频、性能都不一样，所以测试集的大小自己挑个合适的大小就行了，不要太大也不要太小，时间有个一两秒钟就差不多了；

```C
// [...省略]
#include <assert.h>
#include <stdlib.h>
#include <time.h>

// [...省略]

int *generateRandomArray(int n, int rangeL, int rangeR) {
    assert(rangeL <= rangeR);

    int *arr = (int *)malloc(n * sizeof(int));

    srand(time(NULL)); // 随机种子
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;

    return arr;
}
```

## code 

https://github.com/ZengjfOS/RaspberryPi/tree/AlgorithmBaseExample

## log

```
pi@raspberrypi:samples $ ./sort

 11729 24699 27993 16762 6790 25267 13669 14072 1739 11661 12670 17066 14681 28859 17360
 5916 21304 29546 6192 5392 28920 23939 22120 5723 7013 17462 13514 11134 26698 26141
 471 13885

 2 2 3 4 5 6 6 6 8 8 9 10 12 12 13
 14 21 21 21 22 23 26 28 28 31 32 32 33 33 35
 35 37
bubble duration:9.246805 s

 11729 24699 27993 16762 6790 25267 13669 14072 1739 11661 12670 17066 14681 28859 17360
 5916 21304 29546 6192 5392 28920 23939 22120 5723 7013 17462 13514 11134 26698 26141
 471 13885

 2 2 3 4 5 6 6 6 8 8 9 10 12 12 13
 14 21 21 21 22 23 26 28 28 31 32 32 33 33 35
 35 37
insert duration:2.551281 s

 11729 24699 27993 16762 6790 25267 13669 14072 1739 11661 12670 17066 14681 28859 17360
 5916 21304 29546 6192 5392 28920 23939 22120 5723 7013 17462 13514 11134 26698 26141
 471 13885

 2 2 3 4 5 6 6 6 8 8 9 10 12 12 13
 14 21 21 21 22 23 26 28 28 31 32 32 33 33 35
 35 37
select duration:3.441257 s
```

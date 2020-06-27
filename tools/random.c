#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int* generateRandomArray(int n, int rangeL, int rangeR) {
    assert(rangeL <= rangeR);

    int* arr = (int*)malloc(n * sizeof(int));

    srand(time(NULL)); // 随机种子
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;

    return arr;
}

int* copyRandomArray(int* arr_src, int n) {

    int* arr = (int*)malloc(n * sizeof(int));
    memcpy(arr, arr_src, n * sizeof(int));

    return arr;
}

int checkRandomArray(int* arr_src, int n) {
    int i = 0;

    for (i = 0; i < n - 1; i++) {
        if (arr_src[i] > arr_src[i + 1])
            return -1;
    }

    return 0;
}


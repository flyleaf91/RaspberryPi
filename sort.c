#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "timestamp.h"
#include "print.h"
#include "random.h"

#define ARRAY_LENGTH        32000
#define ARRAY_MAX           ARRAY_LENGTH
#define DEBUG_ARRAY_LEN     32


void bubbleSort(int *arr, int n) {
    int i = 0, j = 0;
    int tmp = 0;

    arrayDump(arr, DEBUG_ARRAY_LEN);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    arrayDump(arr, DEBUG_ARRAY_LEN);
}

void selectSort(int *arr, int n) {
    int i = 0, j = 0;
    int k = 0;
    int swap = 0;

    arrayDump(arr, DEBUG_ARRAY_LEN);

    for (i = 0; i < n - 1; i++) {
        k = i;
        for (j = i; j < n; j++) {
            if (arr[k] > arr[j]) {
                k = j;
            }
        }

        swap = arr[i];
        arr[i] = arr[k];
        arr[k] = swap;
    }

    arrayDump(arr, DEBUG_ARRAY_LEN);
}

void insertSort(int *arr, int n) {
    int i = 0, j = 0;
    int tmp = 0;

    arrayDump(arr, DEBUG_ARRAY_LEN);

    for (i = 1; i < n; i++) {
        tmp = arr[i];
        for (j = i; j > 0; j--) {
            if (arr[j - 1] > tmp) {
                arr[j] = arr[j - 1];
            } else 
                break;
        }

        arr[j] = tmp;
    }

    arrayDump(arr, DEBUG_ARRAY_LEN);
}


int main(int argc, char** argv) {

    int* data = generateRandomArray(ARRAY_LENGTH, 0, ARRAY_MAX);
    int* tmp = NULL;
    long long start_time = 0;
    long long end_time = 0;

    tmp = copyRandomArray(data, ARRAY_LENGTH);
    start_time = getMicrosecond();
    bubbleSort(tmp, ARRAY_LENGTH);
    end_time = getMicrosecond();
    if (!checkRandomArray(tmp, ARRAY_LENGTH))
        printf("bubble duration:%lf s\n", (end_time - start_time) / 1000000.0);
    else
        printf("bubble check error\n");
    free(tmp);

    tmp = copyRandomArray(data, ARRAY_LENGTH);
    start_time = getMicrosecond();
    insertSort(tmp, ARRAY_LENGTH);
    end_time = getMicrosecond();
    if (!checkRandomArray(tmp, ARRAY_LENGTH))
        printf("insert duration:%lf s\n", (end_time - start_time) / 1000000.0);
    else
        printf("insert check error\n");
    free(tmp);

    tmp = copyRandomArray(data, ARRAY_LENGTH);
    start_time = getMicrosecond();
    selectSort(tmp, ARRAY_LENGTH);
    end_time = getMicrosecond();
    if (!checkRandomArray(tmp, ARRAY_LENGTH))
        printf("select duration:%lf s\n", (end_time - start_time) / 1000000.0);
    else
        printf("select check error\n");
    free(tmp);

    free(data);
}

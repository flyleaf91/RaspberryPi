#include <stdio.h>

void arrayDump(int *arr, int n) {
    int i = 0;

    for (i = 0; i < n; i++) {
        if ( i % 0xF == 0)
            printf("\n");

        printf(" %d", arr[i]);
    }

    printf("\n");
}

#include <malloc.h>
#include <stdlib.h>
#include "shellSort.h"

// Sort by ascending
void shellSort(int *arr, int size, const int gapArr[], int gapArrSize) {

    if (!arr) return;
    if (size == 0) return;

    // Gap
    int curGap;

    // Counter to traverse gap array
    int i;

    // Current outer
    int j;

    // Current inner
    int k;

    // To save one item
    int tmp;

    // Use gap
    for (i = 0, curGap = gapArr[0]; i < gapArrSize; curGap = gapArr[++i]) {

        for (j = curGap; j < size; j++) {

            // Save item
            tmp = arr[j];

            // Traverse all items in gap sub array selection
            for (k = j; k >= curGap && (arr[k - curGap] > tmp); k -= curGap) {

                // Swap
                arr[k] = arr[k - curGap];
            }

            // Recover saved item
            arr[k] = tmp;
        }
    }
}

// Shell, 1959
gapStruct *rowShell1959(int size) {

    gapStruct *gap = (gapStruct *) malloc(sizeof(gapStruct));

    gap->arr = NULL;
    int curSize = 10;

    gap->arr = (int *) malloc((int) curSize * sizeof(int));

    int i;
    int num;
    for (i = 0, num = size / 2; num > 0; num /= 2, i++) {

        if (i == curSize) {

            curSize *= 2;
            gap->arr = (int *) realloc(gap->arr, (int) curSize * sizeof(int));
        }

        gap->arr[i] = num;

    }

    // Save size
    gap->size = i;

    // Truncate array
    gap->arr = (int *) realloc(gap->arr, (int) gap->size * sizeof(int));

    return gap;
}

// Ciura 2001
gapStruct *rowCiura2001(int size) {

    gapStruct *gap = (gapStruct *) malloc(sizeof(gapStruct));
    gap->size = 9;

    // Ciura sequence
    int tmpArr[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};

    gap->arr = (int *) malloc((int) gap->size * sizeof(int));

    // Copy to dynamic array
    int i;
    for (i = 0; i < gap->size && tmpArr[i] <= size; i++) {

        gap->arr[i] = tmpArr[i];
    }

    // Save size
    gap->size = i;

    // Truncate array
    gap->arr = (int *) realloc(gap->arr, (int) gap->size * sizeof(int));

    return gap;
}
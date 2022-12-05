#include <stdio.h>
#include "libUtils/myArray.h"
#include "libUtils/myTimer.h"
#include "libUtils/myInput.h"
#include "libUtils/myAlloc.h"

#include "libSort/shellSort.h"
#include "libSort/insertionSort.h"

int main(void) {

    int size = 10;

    int *arr = NULL;
    int *tmp = NULL;

    if ((tmp = mallocArrInt(size)) != NULL) {

        arr = tmp;

        arrFillRand(&arr[0], size, 0, size);

        arrPrint(&arr[0], size);

        int gapTmp[5] = {5,4,3,2,1};

//        shellSort(&arr[0], size, gapTmp, 5);

        insertionSort(&arr[0], size);

        arrPrint(&arr[0], size);


        // TODO: temp
        int i;
        for(i = 1; i < size; i++) {

            if (arr[i] < arr[i - 1]) {
                puts("ERROR!");
            }
        }

        gapStruct *tmp1 = rowCiura2001(301);

        arrPrint(&tmp1->arr[0], 10);

    }

    getchar();
    getchar();
    return 0;
}
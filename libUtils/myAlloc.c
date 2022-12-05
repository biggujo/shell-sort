#include <stdlib.h>
#include "myAlloc.h"

// Try to calloc array
int* mallocArrInt(int desiredSize) {

    int *arr = NULL;
    arr = (int *) malloc(desiredSize * sizeof(int));
    return arr ? arr : NULL;
}

// Try to calloc array
int* callocArrInt(int desiredSize) {

    int *arr = NULL;
    arr = (int *) calloc(desiredSize, sizeof(int));
    return arr ? arr : NULL;
}

// Try to realloc array
int* reallocArrInt(int *arr, int desiredSize) {

    int *newArr = NULL;
    newArr = (int *) realloc(arr, desiredSize * sizeof(int));
    return newArr ? newArr : NULL;
}
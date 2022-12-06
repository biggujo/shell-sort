#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "myArray.h"

// Print 1D-array of ints
// 10 items in a row
void arrPrint(int *arr, int size) {

    int i;
    for (i = 0; i < size; i++) {
        printf("%7d", arr[i]);
        if (i % 10 == 9) {
            printf("\n");
        }
    }
    printf("\n");
}

// Fill array with ascending row
void arrFillAsc(int *arr, int size) {

    srand(time(NULL));
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = i ;
    }
}

// Fill array with random numbers
void arrFillRand(int *arr, int size, int min, int max) {

    srand(time(NULL));
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min ;
    }
}

// Fill array with ascending row
void arrFillDesc(int *arr, int size) {

    srand(time(NULL));
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = size - i - 1;
    }
}

// Copy array
void copyArr(int src[], int *dest, int size) {

    int i;
    for (i = 0; i < size; i++) {

        dest[i] = src[i];
    }
}

// Reverse an array
void reverseArr(int *arr, int size) {

    int tmp;
    int i;

    for(i = 0; i < size / 2; i++) {

        // Swap
        tmp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = tmp;
    }
}
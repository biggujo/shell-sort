#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "libUtils/myArray.h"
#include "libUtils/myTimer.h"
#include "libUtils/myInput.h"
#include "libUtils/myAlloc.h"

#define FILE_SHELL1959_TIME_MS      "Shell1959TimeMs.csv"
#define FILE_SHELL1959_COMP         "Shell1959Comp.csv"
#define FILE_SHELL1959_SWAP         "Shell1959Swap.csv"

#define FILE_SEDGEWICK1982_TIME_MS  "Sedgewick1982TimeMs.csv"
#define FILE_SEDGEWICK1982_COMP     "Sedgewick1982Comp.csv"
#define FILE_SEDGEWICK1982_SWAP     "Sedgewick1982Swap.csv"

#define FILE_SEDGEWICK1986_TIME_MS  "Sedgewick1986TimeMs.csv"
#define FILE_SEDGEWICK1986_COMP     "Sedgewick1986Comp.csv"
#define FILE_SEDGEWICK1986_SWAP     "Sedgewick1986Swap.csv"

#define FILE_CIURA2001_TIME_MS      "Ciura2001TimeMs.csv"
#define FILE_CIURA2001_COMP         "Ciura2001Comp.csv"
#define FILE_CIURA2001_SWAP         "Ciura2001Swap.csv"

#define FILE_INSERTION_TIME_MS      "InsertionTimeMs.csv"
#define FILE_INSERTION_COMP         "InsertionComp.csv"
#define FILE_INSERTION_SWAP         "InsertionSwap.csv"

#define FILE_ARRAY_ASC              "ArrayAsc.txt"
#define FILE_ARRAY_DESC             "ArrayDesc.txt"
#define FILE_ARRAY_RAND             "ArrayRand.txt"

typedef struct Array {

    int *arr;
    int size;
} Array;

// Test sort on best, average and worst case
// Output: CSV's with information about time, comparisons and swaps
void testShellRowShell1959(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step);
void testShellRowSedgewick1982(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step);
void testShellRowSedgewick1986(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step);
void testShellRowCiura2001(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step);
void testInsertionSort(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step);

void shellSort(int *arr, int size, const int gapArr[], int gapArrSize);
// Shell, 1959
Array *rowShell1959(int size);
// Sedgewick, 1982
Array* rowSedgewick1982(int size);
// Sedgewick, 1986
Array *rowSedgewick1986(int size);
// Ciura 2001
Array *rowCiura2001(int size);
void insertionSort(int *arr, int size);

int readArraysFromFiles(Array **arrAsc, Array **arrRand, Array **arrDesc, int size);
// Generate arrays, save into files
int generateArraysToFiles(int size);

// Count lines in file
int fileCountLines(char *filename);
// Read int array from text file
int* arrReadFromFile(int *arr, int *size, char *filename);
// Read int array to text file
// Return: 0 - OK, -1 - error
int arrWriteToFile(int arr[], int size, char *filename);

int isAllocated(void *ptr);
void pressAnyKey();
void clrScr();

#define PROGRAM_HEADER "SHELL AND INSERTION COMPARISON TESTS"

static int comparisons = 0;
static int swaps = 0;

int main(void) {

    int size = 1000000;
    int step = size / 10;

    int *arr = NULL;
    int *tmp = NULL;


    Array *arrAsc = NULL;
    Array *arrRand = NULL;
    Array *arrDesc = NULL;

    if (readArraysFromFiles(&arrAsc, &arrRand, &arrDesc, size)) {

        printf("Allocation error!\n");
    }

//    generateArraysToFiles(size);
    testShellRowShell1959(arrAsc, arrRand, arrDesc, size, step);
    testShellRowSedgewick1982(arrAsc, arrRand, arrDesc, size, step);
    testShellRowSedgewick1986(arrAsc, arrRand, arrDesc, size, step);
    testShellRowCiura2001(arrAsc, arrRand, arrDesc, size, step);
//    testInsertionSort(arrAsc, arrRand, arrDesc, size, step);
    puts("Done!");

    getchar();
    getchar();

//    if (arrAsc) {
//        free(arrAsc->arr);
//        free(arrAsc);
//    }
//    if (arrRand) {
//        free(arrRand->arr);
//        free(arrRand);
//    }
//    if (arrDesc) {
//        free(arrDesc->arr);
//        free(arrDesc);
//    }
    return 0;
}

void testShellRowShell1959(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step) {

    int *tmpAlloc = NULL;

    int *arrCopy = NULL;

    // Try to allocate array copy
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return;
    }

    arrCopy = tmpAlloc;

    // For time result
    double timeResult;

    FILE *fileTime = NULL;
    FILE *fileComp = NULL;
    FILE *fileSwap = NULL;

    fopen_s(&fileTime, FILE_SHELL1959_TIME_MS, "w+");
    fopen_s(&fileComp, FILE_SHELL1959_COMP, "w+");
    fopen_s(&fileSwap, FILE_SHELL1959_SWAP, "w+");

    if (!fileTime || !fileComp || !fileSwap) {

        puts("Error opening files!");
        perror("Error: ");
        fflush(stderr);
        return;
    }

    fprintf_s(fileTime, "size, best, average, worst\n");
    fprintf_s(fileComp, "size, best, average, worst\n");
    fprintf_s(fileSwap, "size, best, average, worst\n");

    // Current size of array
    int k;

    Array *testGap;

    for (k = 0; k <= size; k += step) {

        // Create gap
        testGap = rowShell1959(k);

        // Save size to files
        fprintf_s(fileTime, "%d, ", k);
        fprintf_s(fileComp, "%d, ", k);
        fprintf_s(fileSwap, "%d, ", k);

        // Test best case
        copyArr(arrAsc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save best to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test average case
        copyArr(arrRand->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save average to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test worst case
        copyArr(arrDesc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save worst to file
        fprintf_s(fileTime, "%lf\n", timeResult);
        fprintf_s(fileComp, "%d\n", comparisons);
        fprintf_s(fileSwap, "%d\n", swaps);

        comparisons = 0;
        swaps = 0;
    }

    free(arrCopy);

    fclose(fileTime);
    fclose(fileComp);
    fclose(fileSwap);
}

void testShellRowSedgewick1982(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step) {

    int *tmpAlloc = NULL;

    int *arrCopy = NULL;

    // Try to allocate array copy
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return;
    }

    arrCopy = tmpAlloc;

    // For time result
    double timeResult;

    FILE *fileTime = NULL;
    FILE *fileComp = NULL;
    FILE *fileSwap = NULL;

    fopen_s(&fileTime, FILE_SEDGEWICK1982_TIME_MS, "w+");
    fopen_s(&fileComp, FILE_SEDGEWICK1982_COMP, "w+");
    fopen_s(&fileSwap, FILE_SEDGEWICK1982_SWAP, "w+");

    if (!fileTime || !fileComp || !fileSwap) {

        puts("Error opening files!");
        perror("Error: ");
        fflush(stderr);
        return;
    }

    fprintf_s(fileTime, "size, best, average, worst\n");
    fprintf_s(fileComp, "size, best, average, worst\n");
    fprintf_s(fileSwap, "size, best, average, worst\n");

    // Current size of array
    int k;

    Array *testGap;

    for (k = 0; k <= size; k += step) {

        // Create gap
        testGap = rowSedgewick1982(k);
        reverseArr(&testGap->arr[0], testGap->size);

        // Save size to files
        fprintf_s(fileTime, "%d, ", k);
        fprintf_s(fileComp, "%d, ", k);
        fprintf_s(fileSwap, "%d, ", k);

        // Test best case
        copyArr(arrAsc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save best to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test average case
        copyArr(arrRand->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save average to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test worst case
        copyArr(arrDesc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save worst to file
        fprintf_s(fileTime, "%lf\n", timeResult);
        fprintf_s(fileComp, "%d\n", comparisons);
        fprintf_s(fileSwap, "%d\n", swaps);

        comparisons = 0;
        swaps = 0;
    }

    free(arrCopy);

    fclose(fileTime);
    fclose(fileComp);
    fclose(fileSwap);
}

void testShellRowSedgewick1986(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step) {

    int *tmpAlloc = NULL;

    int *arrCopy = NULL;

    // Try to allocate array copy
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return;
    }

    arrCopy = tmpAlloc;

    // For time result
    double timeResult;

    FILE *fileTime = NULL;
    FILE *fileComp = NULL;
    FILE *fileSwap = NULL;

    fopen_s(&fileTime, FILE_SEDGEWICK1986_TIME_MS, "w+");
    fopen_s(&fileComp, FILE_SEDGEWICK1986_COMP, "w+");
    fopen_s(&fileSwap, FILE_SEDGEWICK1986_SWAP, "w+");

    if (!fileTime || !fileComp || !fileSwap) {

        puts("Error opening files!");
        perror("Error: ");
        fflush(stderr);
        return;
    }

    fprintf_s(fileTime, "size, best, average, worst\n");
    fprintf_s(fileComp, "size, best, average, worst\n");
    fprintf_s(fileSwap, "size, best, average, worst\n");

    // Current size of array
    int k;

    Array *testGap;

    for (k = 0; k <= size; k += step) {

        // Create gap
        testGap = rowSedgewick1986(k);
        reverseArr(&testGap->arr[0], testGap->size);

        // Save size to files
        fprintf_s(fileTime, "%d, ", k);
        fprintf_s(fileComp, "%d, ", k);
        fprintf_s(fileSwap, "%d, ", k);

        // Test best case
        copyArr(arrAsc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save best to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test average case
        copyArr(arrRand->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save average to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test worst case
        copyArr(arrDesc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save worst to file
        fprintf_s(fileTime, "%lf\n", timeResult);
        fprintf_s(fileComp, "%d\n", comparisons);
        fprintf_s(fileSwap, "%d\n", swaps);

        comparisons = 0;
        swaps = 0;
    }

    free(arrCopy);

    fclose(fileTime);
    fclose(fileComp);
    fclose(fileSwap);
}

void testShellRowCiura2001(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step) {

    int *tmpAlloc = NULL;

    int *arrCopy = NULL;

    // Try to allocate array copy
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return;
    }

    arrCopy = tmpAlloc;

    // For time result
    double timeResult;

    FILE *fileTime = NULL;
    FILE *fileComp = NULL;
    FILE *fileSwap = NULL;

    fopen_s(&fileTime, FILE_CIURA2001_TIME_MS, "w+");
    fopen_s(&fileComp, FILE_CIURA2001_COMP, "w+");
    fopen_s(&fileSwap, FILE_CIURA2001_SWAP, "w+");

    if (!fileTime || !fileComp || !fileSwap) {

        puts("Error opening files!");
        perror("Error: ");
        fflush(stderr);
        return;
    }

    fprintf_s(fileTime, "size, best, average, worst\n");
    fprintf_s(fileComp, "size, best, average, worst\n");
    fprintf_s(fileSwap, "size, best, average, worst\n");

    // Current size of array
    int k;

    Array *testGap;

    for (k = 0; k <= size; k += step) {

        // Create gap
        testGap = rowCiura2001(k);
        reverseArr(&testGap->arr[0], testGap->size);

        // Save size to files
        fprintf_s(fileTime, "%d, ", k);
        fprintf_s(fileComp, "%d, ", k);
        fprintf_s(fileSwap, "%d, ", k);

        // Test best case
        copyArr(arrAsc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save best to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test average case
        copyArr(arrRand->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save average to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test worst case
        copyArr(arrDesc->arr, &arrCopy[0], k);

        startTimer();
        shellSort(&arrCopy[0], k, testGap->arr, testGap->size);
        timeResult = stopTimer();

        // Save worst to file
        fprintf_s(fileTime, "%lf\n", timeResult);
        fprintf_s(fileComp, "%d\n", comparisons);
        fprintf_s(fileSwap, "%d\n", swaps);

        comparisons = 0;
        swaps = 0;
    }

    free(arrCopy);

    fclose(fileTime);
    fclose(fileComp);
    fclose(fileSwap);
}

void testInsertionSort(Array *arrAsc, Array *arrRand, Array *arrDesc, int size, int step) {

    int *tmpAlloc = NULL;

    int *arrCopy = NULL;

    // Try to allocate array copy
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return;
    }

    arrCopy = tmpAlloc;

    // For time result
    double timeResult;

    FILE *fileTime = NULL;
    FILE *fileComp = NULL;
    FILE *fileSwap = NULL;

    fopen_s(&fileTime, FILE_INSERTION_TIME_MS, "w+");
    fopen_s(&fileComp, FILE_INSERTION_COMP, "w+");
    fopen_s(&fileSwap, FILE_INSERTION_SWAP, "w+");

    if (!fileTime || !fileComp || !fileSwap) {

        puts("Error opening files!");
        perror("Error: ");
        fflush(stderr);
        return;
    }

    fprintf_s(fileTime, "size, best, average, worst\n");
    fprintf_s(fileComp, "size, best, average, worst\n");
    fprintf_s(fileSwap, "size, best, average, worst\n");

    // Current size of array
    int k;

    Array *testGap;

    for (k = 0; k <= size; k += step) {

        // Save size to files
        fprintf_s(fileTime, "%d, ", k);
        fprintf_s(fileComp, "%d, ", k);
        fprintf_s(fileSwap, "%d, ", k);

        // Test best case
        copyArr(arrAsc->arr, &arrCopy[0], k);

        startTimer();
        insertionSort(&arrCopy[0], k);
        timeResult = stopTimer();

        // Save best to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test average case
        copyArr(arrRand->arr, &arrCopy[0], k);

        startTimer();
        insertionSort(&arrCopy[0], k);
        timeResult = stopTimer();

        // Save average to file
        fprintf_s(fileTime, "%lf, ", timeResult);
        fprintf_s(fileComp, "%d, ", comparisons);
        fprintf_s(fileSwap, "%d, ", swaps);

        comparisons = 0;
        swaps = 0;

        // Test worst case
        copyArr(arrDesc->arr, &arrCopy[0], k);

        startTimer();
        insertionSort(&arrCopy[0], k);
        timeResult = stopTimer();

        // Save worst to file
        fprintf_s(fileTime, "%lf\n", timeResult);
        fprintf_s(fileComp, "%d\n", comparisons);
        fprintf_s(fileSwap, "%d\n", swaps);

        comparisons = 0;
        swaps = 0;
    }

    free(arrCopy);

    fclose(fileTime);
    fclose(fileComp);
    fclose(fileSwap);
}

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

        comparisons++;

        for (j = curGap; j < size; j++) {

            comparisons++;

            // Save item
            tmp = arr[j];

            // Traverse all items in gap sub array selection
            for (k = j; k >= curGap && (arr[k - curGap] > tmp); k -= curGap) {

                comparisons++;

                swaps++;

                // Swap
                arr[k] = arr[k - curGap];
            }

            comparisons++;

            swaps++;

            // Recover saved item
            arr[k] = tmp;
        }

        comparisons++;
    }

    comparisons++;
}

// Shell, 1959
Array *rowShell1959(int size) {

    Array *gap = (Array *) malloc(sizeof(Array));

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

// Sedgewick, 1982
Array* rowSedgewick1982(int size) {

    Array *gap = (Array *) malloc(sizeof(Array));

    gap->arr = NULL;
    int curSize = 10;

    gap->arr = (int *) malloc((int) curSize * sizeof(int));

    int i;
    int num1 = 4;
    int num2 = 3;

    gap->arr[0] = 1;
    for (i = 1; num1 + num2 + 1 < size; num1 *= 4, num2 *= 2, i++) {

        if (i == curSize) {

            curSize *= 2;
            gap->arr = (int *) realloc(gap->arr, (int) curSize * sizeof(int));
        }

        gap->arr[i] = num1 + num2 + 1;
    }

    // Save size
    gap->size = i;

    // Truncate array
    gap->arr = (int *) realloc(gap->arr, (int) gap->size * sizeof(int));

    return gap;
}

// Sedgewick, 1986
Array *rowSedgewick1986(int size) {

    Array *gap = (Array *) malloc(sizeof(Array));

    gap->arr = NULL;
    int curSize = 10;

    gap->arr = (int *) malloc((int) curSize * sizeof(int));

    int i;
    int num1;
    int num2;
    int num3;

    gap->arr[0] = 1;
    for (i = 0;; i++) {

        num1 = 2 << i;
        num2 = 2 << (i / 2);
        num3 = 2 << (i + 1) / 2;

        if (i + 1 == curSize) {

            curSize *= 2;
            gap->arr = (int *) realloc(gap->arr, (int) curSize * sizeof(int));
        }

        if (i & 1) {

            gap->arr[i + 1] = (int) 9 * (num1 - num2) + 1;
        }
        else {

            gap->arr[i + 1] = (int) (8 * num1 - 6 * num3 + 1);
        }

        if (gap->arr[i] >= size) {

            break;
        }
    }

    // Save size
    gap->size = i;

    // Truncate array
    gap->arr = (int *) realloc(gap->arr, (int) gap->size * sizeof(int));

    return gap;
}

// Ciura 2001
Array *rowCiura2001(int size) {

    Array *gap = (Array *) malloc(sizeof(Array));
    gap->size = 8;

    // Ciura sequence
    int tmpArr[8] = {1, 4, 10, 23, 57, 132, 301, 701};

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

// Sort by ascending
void insertionSort(int arr[], int size) {

    // Outer counter
    int i;

    // Inner counter
    int j;

    // Key item all items compared with
    int key;

    for (i = 1; i < size; i++) {

        comparisons++;

        // Save item
        key = arr[i];

        // Traverse and swap all items to the start before correct position is found
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {

            comparisons++;

            swaps++;

            arr[j + 1] = arr[j];
        }

        comparisons++;

        swaps++;

        // Recover saved item in the correct position
        arr[j + 1] = key;
    }

    comparisons++;
}

// Read array from files
// Return: 0 - OK, 1 - Error
int readArraysFromFiles(Array **arrAsc, Array **arrRand, Array **arrDesc, int size) {

    *arrAsc = (Array *) calloc(1, sizeof(Array));
    *arrRand = (Array *) calloc(1, sizeof(Array));
    *arrDesc = (Array *) calloc(1, sizeof(Array));

    if (!arrAsc || !arrRand || !arrDesc) {

        return 1;
    }

    int *tmpAlloc = NULL;

    tmpAlloc = NULL;

    // Allocate array by ascending
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return 1;
    }

    // Save pointer
    (*arrAsc)->arr = tmpAlloc;

    tmpAlloc = NULL;

    // Allocate array by ascending
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return 1;
    }

    // Save pointer
    (*arrDesc)->arr = tmpAlloc;

    tmpAlloc = NULL;

    // Allocate for random array
    tmpAlloc = mallocArrInt(size);
    if (!isAllocated(tmpAlloc)) {

        printf("Allocation error!\n");
        return 1;
    }

    // Save pointer
    (*arrRand)->arr = tmpAlloc;

    tmpAlloc = NULL;

    // Fill array
    arrReadFromFile(&(*arrAsc)->arr[0], &size, FILE_ARRAY_ASC);
    arrReadFromFile(&(*arrDesc)->arr[0], &size, FILE_ARRAY_DESC);
    arrReadFromFile(&(*arrRand)->arr[0], &size, FILE_ARRAY_RAND);

    return 0;
}

// Generate arrays, save into files
// Return: 0 - OK, 1 - Error
int generateArraysToFiles(int size) {

    int *arr;

    // Generate by ascending
    arr = mallocArrInt(size);
    arrFillAsc(&arr[0], size);
    if (arrWriteToFile(&arr[0], size, FILE_ARRAY_ASC)) {
        perror("Error: ");
        return 1;
    }
    free(arr);

    // Generate random
    arr = mallocArrInt(size);
    arrFillRand(&arr[0], size, 0, size);
    if (arrWriteToFile(&arr[0], size, FILE_ARRAY_RAND)) {
        perror("Error: ");
        return 1;
    }
    free(arr);

    // Generate by descending
    arr = mallocArrInt(size);
    arrFillDesc(&arr[0], size);
    if (arrWriteToFile(&arr[0], size, FILE_ARRAY_DESC)) {
        perror("Error: ");
        return 1;
    }
    free(arr);

    return 1;
}

// Count lines in file
// Return: amount of lines or 0 if error
int fileCountLines(char *filename) {

    // Try to open file
    FILE *fp = NULL;
    fopen_s(&fp, filename, "r");

    int lines = 0;

    // If opened
    if (fp) {

        // Count lines
        char ch;
        for (ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {

            if (ch == '\n') lines++;
        }

        fclose(fp);
    }

    return lines;
}

// Read int array from text file
// Return: arr or NULL
int* arrReadFromFile(int *arr, int *size, char *filename) {

    // Try to open file
    FILE *fp = NULL;
    fopen_s(&fp, filename, "r");

    // If opened
    if (!fp) return NULL;

    int *tmp;
    int lines = fileCountLines(filename);

    // Reallocate to proper size
    if ((tmp = (int *) realloc(arr, sizeof(int) * lines)) != NULL) {

        *size = lines;

        arr = tmp;

        // Fill from file
        int i;
        for (i = 0; i < lines; ++i) {

            fscanf(fp, "%d", &arr[i]);
        }
    }
    fclose(fp);
    return arr;
}

// Read int array to text file
// Return: 0 - OK, -1 - error
int arrWriteToFile(int arr[], int size, char *filename) {

    // Try to open file
    FILE *fp = NULL;
    fopen_s(&fp, filename, "w+");

    // If opened
    if (!fp) return -1;

    int i;
    for (i = 0; i < size; i++) {

        fprintf_s(fp, "%d\n", arr[i]);
    }

    fclose(fp);

    return 0;
}

int isAllocated(void *ptr) {

    return ptr ? 1 : 0;
}

void clrScr() {

    system("cls");
    printf("%s\n\n", PROGRAM_HEADER);
}

void pressAnyKey() {

    printf("Press any key to continue...");
    getch();

}
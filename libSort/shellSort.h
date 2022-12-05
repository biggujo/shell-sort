#ifndef SHELL_SORT_COURSE_WORK_SHELLSORT_H
#define SHELL_SORT_COURSE_WORK_SHELLSORT_H

typedef struct gapStruct {

    int *arr;
    int size;
} gapStruct;

// Sort by ascending
void shellSort(int *arr, int size, const int gapArr[], int gapArrSize);
gapStruct *rowShell1959(int size);
gapStruct *rowCiura2001(int size);

#endif //SHELL_SORT_COURSE_WORK_SHELLSORT_H

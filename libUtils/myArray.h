#ifndef SHELL_SORT_COURSE_WORK_MYARRAY_H
#define SHELL_SORT_COURSE_WORK_MYARRAY_H

// Fill array with ascending row
void arrFillAsc(int *arr, int size);
// Fill array with random numbers
void arrFillRand(int *arr, int size, int min, int max);
// Fill array with ascending row
void arrFillDesc(int *arr, int size);

// Copy array
void copyArr(int src[], int *dest, int size);
// Reverse an array
void reverseArr(int *arr, int size);

// Print 1D-array
void arrPrint(int *arr, int size);

#endif //SHELL_SORT_COURSE_WORK_MYARRAY_H

#include "insertionSort.h"

// Sort by ascending
void insertionSort(int arr[], int size) {

    // Outer counter
    int i;

    // Inner counter
    int j;

    // Key item all items compared with
    int key;

    for (i = 1; i < size; i++) {

        // Save item
        key = arr[i];

        // Traverse and swap all items to the start before correct position is found
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {

            arr[j + 1] = arr[j];
        }

        // Recover saved item in the correct position
        arr[j + 1] = key;
    }
}
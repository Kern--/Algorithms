#include <limits.h>
#include <stdbool.h>
#include "sort.h"
#include "util.h"

void bubbleSort(int array[], const size_t len) {
    bool hasChanges = true;
    while (hasChanges) {
        hasChanges = false;
        for (int i = 0; i < len - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i+1]);
                hasChanges = true;
            }
        }
    }
}

void selectionSort(int array[], const size_t len) {
    // For each index in the array,
    //   find the smallest value from i to end of the array
    //   swap the smallest element with the element at i
    // As we go through, the array from 0 to i-1 should be sorted
    // At each step we select the next sorted element to go to i
    // Therefore, when i == len, the array will be sorted from 0 to len-1
    //  which means the whole list will be sorted

    // Keep track of the index with the smallest value
    size_t smallestIndex;
    for (size_t i = 0; i < len; ++i) {
        // Every value before index i is guaranteed to be smaller or equal to the value at index i
        smallestIndex = i;
        for (size_t j = i; j < len; ++j) {
            if (array[j] < array[smallestIndex]) {
                smallestIndex = j;
            }
        }
        swap(&array[i], &array[smallestIndex]);
    }   
}


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

void insertionSort(int array[], const size_t len) {
    // For each index in the array
    //  find the index between 0 and the current index for which inserting the current element would result in a sorted list
    //  push all elements from insertion point to current index up on index
    //  insert the current element at the insertion point
    // At each index i, we have sorted up to index i - 1
    //  At each step, we insert the element at i into the correct position in the array between 0 and i such that the array
    //     sorted from 0 to i
    //  Therefore, when i == len, we will insert the element such that the array is sorted from 0 to len, which means that 
    //     the entire array will be sorted
    
    // Keep track of the current value we're trying to insert
    int currentValue;
    // Keep track of the index we want to insert after
    size_t j;
    for (size_t i = 0; i < len; ++i) {
        currentValue = array[i];
        for (j = i; j > 0; --j) {
            if (currentValue > array[j - 1]) {
                // The preceeding item is smaller, this is the index we want
                break;
            }
            // Current element goes earlier, push the one at j - 1 up one index to make space
            array[j] = array[j - 1];
        }
        // Either we went through everthing from i down to 0 or we found some element at index j - 1 that
        //  was smaller than the current element. Either way, the current element goes where we ended
        array[j] = currentValue;
    }
}

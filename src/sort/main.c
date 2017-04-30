// This file is acting as a quick sanity check.
//  Real tests with timings and multiple array configurations will exist eventually

#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include "util.h"

#define TEST_ARRAY_SIZE 20

void print(const int array[], const size_t len) {
    printf("[");
    for (int i = 0; i < len; ++i) {
        printf("%d", array[i]);
        if (i < len - 1) {
            printf(", ");
        }    
    }
    printf("]\n");
}

int main() {
    // Create an array and fill it in ascending order
    int array[TEST_ARRAY_SIZE];
    for (int i = 0; i < TEST_ARRAY_SIZE; ++i) {
        array[i] = i;
    } 

    // Shuffle the array
    for (int i = 2; i < TEST_ARRAY_SIZE; ++i) {
        int j = rand() % i;
        swap(&array[i], &array[j]);
    }

    // Sort and print array before/after
    print(array, TEST_ARRAY_SIZE);
    mergeSort(array, TEST_ARRAY_SIZE);
    print(array, TEST_ARRAY_SIZE);
}


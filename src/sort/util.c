#include <stdlib.h>
#include "util.h"

int *generateAscendingArray(const size_t len) {
    int *array = (int *)malloc(len * sizeof(int));
    for (size_t i = 0; i < len; ++i) {
        array[i] = (int)i;
    }
    return array;
}

int *generateDescendingArray(const size_t len) {
    int *array = (int *)malloc(len * sizeof(int));
    for (size_t i = 0; i < len; ++i) {
        array[i] = (int)(len - i);
    }
    return array;
}

int *generateRandomArray(const size_t len) {
    int *array = generateAscendingArray(len);
    shuffle(array, len);
    return array;   
}

void shuffle(int array[], const size_t len) {
    for (size_t i = 1; i < len; ++i) {
        size_t j = (size_t)rand() % i;
	swap(&array[i], &array[j]);
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

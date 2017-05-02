#include <stdlib.h>
#include "util.h"

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

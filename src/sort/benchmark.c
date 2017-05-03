#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "util.h"

// A method to test stuff
void test(SortFunc sort, const size_t arraySize, const size_t runs);

int main() {
    const size_t array_size = 30000;
    const size_t runs = 10;

    printf("Bubble Sort\n");
    test(&bubbleSort, array_size, runs);

    printf("\n\nInsertion Sort\n");
    test(&insertionSort, array_size, runs);

    printf("\n\nSelection Sort\n");
    test(&insertionSort, array_size, runs);

    printf("\n\nMerge Sort\n");
    test(&mergeSort, array_size, runs);

    printf("\n\nQuick Sort\n");
    test(&quickSort, array_size, runs);
}

void test(SortFunc sort, const size_t arraySize, const size_t runs) {
    volatile clock_t start;
    volatile clock_t end;
    clock_t *timing = (clock_t *)malloc(runs * sizeof (clock_t));
    clock_t average = 0;
    for (size_t i = 0; i < runs; ++i) {
        int *array = generateRandomArray(arraySize);
        start = clock();
        sort(array, arraySize);
        end = clock();
        timing[i] = end - start;
        average += timing[i];
        printf("RUN[%zu]: %lu cycles (%lu ms)\n", i, timing[i], timing[i] * 1000 / CLOCKS_PER_SEC);
        free(array);
    }
    average /= runs;
    printf("\nAVERAGE: %lu cycles (%lu ms)\n", average, average * 1000 / CLOCKS_PER_SEC);
    free(timing);
}


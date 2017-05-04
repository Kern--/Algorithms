#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "test.h"
#include "util.h"

#define len(a) sizeof (a) / sizeof (a[0])

// A method to test stuff
void test(SortFuncInfo sort, const size_t arraySize, const size_t runs);

static SortFuncInfo sorts[] = {
    { bubbleSort, "Bubble Sort" },
    { insertionSort, "Insertion Sort" },
    { selectionSort, "Selection Sort" },
    { mergeSort, "Merge Sort" },
    { quickSort, "Quick Sort" }
};


int main() {
    const size_t array_size = 30000;
    const size_t runs = 10;

    size_t numSorts = len(sorts);
    for (size_t i = 0; i < numSorts; ++i) {
        test(sorts[i], array_size, runs);   
    }
}

void test(SortFuncInfo sort, const size_t arraySize, const size_t runs) {
    volatile clock_t start;
    volatile clock_t end;
    clock_t *timing = (clock_t *)malloc(runs * sizeof (clock_t));
    clock_t average = 0;
    
    printf("%s\n", sort.name); 
    for (size_t i = 0; i < runs; ++i) {
        int *array = generateRandomArray(arraySize);
        start = clock();
        sort.sort(array, arraySize);
        end = clock();
        timing[i] = end - start;
        average += timing[i];
        printf("RUN[%zu]: %lu cycles (%lu ms)\n", i, timing[i], timing[i] * 1000 / CLOCKS_PER_SEC);
        free(array);
    }
    average /= runs;
    printf("\nAVERAGE: %lu cycles (%lu ms)\n\n", average, average * 1000 / CLOCKS_PER_SEC);
    free(timing);
}


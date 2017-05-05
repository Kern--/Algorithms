#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "test.h"
#include "util.h"

#define len(a) sizeof (a) / sizeof (a[0])

// A method to test stuff
void test(SortFuncInfo sort, const size_t arraySize, const size_t runs);

// A function to perform a single test of a sort function
clock_t test_single(SortFunc sort, const size_t arraySize, const ArrayDirection direction);

// A function for generating an array with a given default sort order
int *generateArray(const size_t size, const ArrayDirection direction);

static SortFuncInfo sorts[] = {
    { bubbleSort, "Bubble Sort" },
    { insertionSort, "Insertion Sort" },
    { selectionSort, "Selection Sort" },
    { mergeSort, "Merge Sort" },
    { quickSort, "Quick Sort" }
};


int main() {
    const size_t array_size = 10000;
    const size_t runs = 10;

    size_t numSorts = len(sorts);
    for (size_t i = 0; i < numSorts; ++i) {
        test(sorts[i], array_size, runs);   
    }
}

void test(SortFuncInfo sort, const size_t arraySize, const size_t runs) {
    clock_t *timing = (clock_t *)malloc(runs * sizeof (clock_t));
    clock_t average = 0;
    
    printf("%s\n", sort.name); 
    for (size_t i = 0; i < runs; ++i) {
        timing[i] = test_single(sort.sort, arraySize, RANDOM);
        average += timing[i];
        printf("RUN[%zu]: %lu cycles (%lu ms)\n", i, timing[i], timing[i] * 1000 / CLOCKS_PER_SEC);
    }
    average /= runs;
    printf("\nAVERAGE: %lu cycles (%lu ms)\n\n", average, average * 1000 / CLOCKS_PER_SEC);
    free(timing);
}

clock_t test_single(SortFunc sort, const size_t arraySize, const ArrayDirection direction) {
    clock_t start;
    clock_t end;

    int *array = generateArray(arraySize, direction);
    start = clock();
    sort(array, arraySize);
    end = clock();
    
    free(array);
    return end - start;
}

int *generateArray(const size_t size, const ArrayDirection direction) {
    switch (direction) {
        case ASCENDING:
            return generateAscendingArray(size);
        case DESCENDING:
            return generateDescendingArray(size);
        case RANDOM:
            return generateRandomArray(size);
    }
}

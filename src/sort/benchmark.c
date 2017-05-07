#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "test.h"
#include "util.h"

#define len(a) sizeof (a) / sizeof (a[0])

// A method to test stuff
clock_t *test(SortFuncInfo sort, const size_t arraySize, const size_t runs);

// A function to perform a single test of a sort function
clock_t test_single(SortFunc sort, const size_t arraySize, const ArrayDirection direction);

// A function for generating an array with a given default sort order
int *generateArray(const size_t size, const ArrayDirection direction);

clock_t *runTestSuite(SortFuncInfo sort, const size_t tests[], const size_t numTests, const size_t runs);

clock_t average(const clock_t array[], const size_t arraySize);

clock_t cyclesToMs(const clock_t cycles);

void printTestSizes(const size_t tests[], const size_t arraySize);

void printTestResults(const char label[], const clock_t results[], const size_t arraySize);

static SortFuncInfo sorts[] = {
    { bubbleSort, "Bubble Sort" },
    { insertionSort, "Insertion Sort" },
    { selectionSort, "Selection Sort" },
    { mergeSort, "Merge Sort" },
    { quickSort, "Quick Sort" }
};

static size_t testSizes[] = { 100, 500, 1000, 2000, 3000, 4000, 5000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 100000 };


int main() {
    const size_t runs = 1;
    const size_t numTests = len(testSizes);

    printTestSizes(testSizes, numTests);
    size_t numSorts = len(sorts);
    for (size_t i = 0; i < numSorts; ++i) {
        clock_t *averages = runTestSuite(sorts[i], testSizes, numTests, runs);
        printTestResults(sorts[i].name, averages, numTests);
        free(averages);
    }
}

clock_t *runTestSuite(SortFuncInfo sort, const size_t tests[], const size_t numTests, const size_t runs) {
    clock_t *averageMs = (clock_t *)malloc(numTests * sizeof (clock_t));
    for (size_t i = 0; i < numTests; ++i) {
        clock_t *results = test(sort, tests[i], runs);
        averageMs[i] = cyclesToMs(average(results, runs));
        free(results);
    }
    return averageMs;
}

clock_t *test(SortFuncInfo sort, const size_t arraySize, const size_t runs) {
    clock_t *timing = (clock_t *)malloc(runs * sizeof (clock_t));
    for (size_t i = 0; i < runs; ++i) {
        timing[i] = test_single(sort.sort, arraySize, RANDOM);
    }
    return timing;
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

clock_t average(const clock_t array[], const size_t arraySize) {
    clock_t ave = 0;
    for (size_t i = 0; i < arraySize; ++i) {
        ave += (array[i] / arraySize);
    }
    return ave;
}

clock_t cyclesToMs(const clock_t cycles) {
    return cycles * 1000 / CLOCKS_PER_SEC;
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

void printTestSizes(const size_t tests[], const size_t arraySize) {
    printf("                    ");
    for (size_t i = 0; i < arraySize; ++i) {
        printf("%-4zu\t", tests[i]);
    }
    printf("\n");
}

void printTestResults(const char label[], const clock_t testResults[], const size_t arraySize) {
    printf("%-20s", label);
    for (size_t i = 0; i < arraySize; ++i) {
        printf("%-4zums\t", testResults[i]);
    }
    printf("\n");
}


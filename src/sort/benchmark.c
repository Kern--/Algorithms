#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "test.h"
#include "util.h"

#define len(a) sizeof (a) / sizeof (a[0])

// A method to test stuff
clock_t *test(SortFuncInfo sort, const size_t arraySize, const ArrayDirection arrayDirection, const size_t runs);

// A function to perform a single test of a sort function
clock_t test_single(SortFunc sort, const size_t arraySize, const ArrayDirection direction);

// A function for generating an array with a given default sort order
int *generateArray(const size_t size, const ArrayDirection direction);

// Runs a suite of tests against a sort function. For each test size, an array is generated of that size in the specified initial sort direction.
//  This process is repeated runs times and the average is placed in the return result at the same index as the array size. At the end, returns
//  an array of the average number of clocks spent sorting the array for each test size
clock_t *runTestSuite(SortFuncInfo sort, const size_t tests[], const size_t numTests, const ArrayDirection arrayDirection, const size_t runs);

// Computes the average of an array of clock_t
clock_t average(const clock_t array[], const size_t arraySize);

// Converts cycles to milliseconds
clock_t cyclesToMs(const clock_t cycles);

// Converts an ArrayDirection to a name that describes it (This should probably be handled differently)
const char *directionName(ArrayDirection direction);

// Prints out a list of array sizes to be tested in a format that's useful for building a table of results
void printTestSizes(const size_t tests[], const size_t arraySize);

// Prints out the results of tests along with a label for use in building a table of results
void printTestResults(const char label[], const clock_t results[], const size_t arraySize);

static SortFuncInfo sorts[] = {
    { bubbleSort, "Bubble Sort" },
    { insertionSort, "Insertion Sort" },
    { selectionSort, "Selection Sort" },
    { mergeSort, "Merge Sort" },
    { quickSort, "Quick Sort" }
};

static ArrayDirection testArrayDirections[] = { RANDOM, ASCENDING, DESCENDING };
static size_t testSizes[] = { 100, 500, 1000, 2000, 3000, 4000, 5000, 10000, 15000, 20000, 25000, 30000, 40000, 50000, 75000, 100000 };


int main() {
    const size_t runs = 10;
    const size_t numArraySizes = len(testSizes);
    const size_t numArrayDirections = len(testArrayDirections);
    size_t numSorts = len(sorts);

    for (size_t i = 0; i < numArrayDirections; ++i) {
        printf("Benchmarking sorts against a %s array\n", directionName(testArrayDirections[i])); 
        printTestSizes(testSizes, numArraySizes);
        for (size_t j = 0; j < numSorts; ++j) {
            clock_t *averages = runTestSuite(sorts[j], testSizes, numArraySizes, testArrayDirections[i], runs);
            printTestResults(sorts[j].name, averages, numArraySizes);
            free(averages);
        }
    }
}

clock_t *runTestSuite(SortFuncInfo sort, const size_t tests[], const size_t numTests, ArrayDirection arrayDirection, const size_t runs) {
    clock_t *averageMs = (clock_t *)malloc(numTests * sizeof (clock_t));
    for (size_t i = 0; i < numTests; ++i) {
        clock_t *results = test(sort, tests[i], arrayDirection, runs);
        averageMs[i] = cyclesToMs(average(results, runs));
        free(results);
    }
    return averageMs;
}

clock_t *test(SortFuncInfo sort, const size_t arraySize, const ArrayDirection arrayDirection, const size_t runs) {
    clock_t *timing = (clock_t *)malloc(runs * sizeof (clock_t));
    for (size_t i = 0; i < runs; ++i) {
        timing[i] = test_single(sort.sort, arraySize, arrayDirection);
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

const char *directionName(ArrayDirection direction) {
    switch (direction) {
        case ASCENDING:
            return "ascending";
        case DESCENDING:
            return "descending";
        case RANDOM:
            return "random";
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


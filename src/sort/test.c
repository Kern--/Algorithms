#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "test.h"
#include "util.h"

#define len(array) sizeof(array)/sizeof(array[0])
#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"


static const char PASS[] = "OK";
static const char FAIL[] = "FAILED";

bool verify(const int array[], const size_t len); 
void test(SortFuncInfo info, TestConfiguration test);

static SortFuncInfo sorts[] = {
  { bubbleSort,    "Bubble Sort" },
  { insertionSort, "Insertion Sort" },
  { selectionSort, "Selection Sort" },
  { mergeSort,     "Merge Sort" },
  { quickSort,     "Quick Sort" }
};

static TestConfiguration tests[] = { 
    { generateAscendingArray,  100,  "Ascending" },
    { generateDescendingArray, 100,  "Descending" },
    { generateRandomArray,     100,  "Random" },
    { generateAscendingArray,  1000, "Ascending" },
    { generateDescendingArray, 1000, "Descending" },
    { generateRandomArray,     1000, "Random" },
};

int main() {
    size_t numSorts = len(sorts);
    size_t numTests = len(tests);

    for (size_t i = 0 ; i < numSorts; ++i) {
        for (size_t j = 0; j < numTests; ++j) {
            test(sorts[i], tests[j]);
        }
    }
}

void test(SortFuncInfo info, TestConfiguration config) {
    int *array = config.gen(config.len);   
    info.sort(array, config.len);
    bool success = verify(array, config.len);
    const char *message = success ? PASS : FAIL;
    const char *color = success ? GREEN : RED;
    printf("%-15s %-5zu %-15s - %s%s%s\n", info.name, config.len, config.name, color, message, RESET);
    free(array); 
}

bool verify(const int array[], const size_t len) {
    for (size_t i = 1; i < len; ++i) {
       if (array[i] < array[i-1]) {
           return false;
       }
    }
    return true;
}


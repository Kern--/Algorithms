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


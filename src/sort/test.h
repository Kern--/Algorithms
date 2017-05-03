#pragma once

#include "util.h"

typedef struct {
    SortFunc sort;
    const char* const name;
} SortFuncInfo;

typedef struct {
    ArrayGenerator gen;
    const size_t len;
    const char* const name;
} TestConfiguration;


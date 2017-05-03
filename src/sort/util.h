#pragma once

// A convenience typedef for passing sort functions
typedef void (* SortFunc)(int array[], const size_t len);

// A convenience typedef for passing array generating functions
typedef int *(* ArrayGenerator)(const size_t len);

// Generates an array of length len with elements in ascending order
int *generateAscendingArray(const size_t len);

// Generates an array of length len with elements in descending order
int *generateDescendingArray(const size_t len);

// Generates an array of length len with elements in a random order
int *generateRandomArray(const size_t len);

// Shuffles an array guaranteeing no element ends in it's original place
void shuffle(int array[], const size_t len);

// Swaps a pair of integers
void swap(int *a, int *b);


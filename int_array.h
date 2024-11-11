//
// Created by Angel Miranda on 29/10/24.
//

#ifndef THIRD_PRACTICE_INT_ARRAY_H
#define THIRD_PRACTICE_INT_ARRAY_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *data;
    size_t size;
} IntArray;

void initIntArray(IntArray *array);

void appendIntArray(IntArray *array, int value);

void popIntArray(IntArray *array);

void freeIntArray(IntArray *array);

#endif //THIRD_PRACTICE_INT_ARRAY_H

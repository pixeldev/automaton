//
// Created by Angel Miranda on 29/10/24.
//

#ifndef THIRD_PRACTICE_CHAR_ARRAY_H
#define THIRD_PRACTICE_CHAR_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t size;
} CharArray;

void initCharArray(CharArray *array);

void appendCharArray(CharArray *array, char value);

void freeCharArray(CharArray *array);

#endif //THIRD_PRACTICE_CHAR_ARRAY_H

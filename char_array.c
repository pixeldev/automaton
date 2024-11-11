//
// Created by Angel Miranda on 29/10/24.
//

#include "char_array.h"

void initCharArray(CharArray *array) {
    array->data = NULL;
    array->size = 0;
}

void appendCharArray(CharArray *array, char value) {
    char *new_data = (char *) realloc(array->data, (array->size + 1) * sizeof(char));
    if (new_data == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    array->data = new_data;
    array->data[array->size] = value;
    array->size += 1;
}

void freeCharArray(CharArray *array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
}
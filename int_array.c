//
// Created by Angel Miranda on 29/10/24.
//

#include "int_array.h"

void initIntArray(IntArray *array) {
    array->data = NULL;
    array->size = 0;
}

void appendIntArray(IntArray *array, int value) {
    int *new_data = (int *) realloc(array->data, (array->size + 1) * sizeof(int));
    if (new_data == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    array->data = new_data;
    array->data[array->size] = value;
    array->size += 1;
}

void popIntArray(IntArray *array) {
    if (array->size > 0) {
        array->size -= 1;

        int *new_data = (int *) realloc(array->data, array->size * sizeof(int));
        if (new_data == NULL) {
            printf("Error al asignar memoria.\n");
            exit(1);
        }

        array->data = new_data;
    }
}

void freeIntArray(IntArray *array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
}
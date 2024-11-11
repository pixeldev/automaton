//
// Created by Angel Miranda on 29/10/24.
//

#include "transition.h"

void initTransitionArray(TransitionArray *array) {
    array->data = NULL;
    array->size = 0;
}

void appendTransitionArray(TransitionArray *array, Transition value) {
    Transition *new_data = (Transition *) realloc(array->data, (array->size + 1) * sizeof(Transition));
    if (new_data == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    array->data = new_data;
    array->data[array->size] = value;
    array->size += 1;
}

void freeTransitionArray(TransitionArray *array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
}
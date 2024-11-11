//
// Created by Angel Miranda on 29/10/24.
//

#ifndef THIRD_PRACTICE_TRANSITION_H
#define THIRD_PRACTICE_TRANSITION_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int from_state;
    char input_symbol;
    int to_state;
} Transition;

typedef struct {
    Transition *data;
    size_t size;
} TransitionArray;

void initTransitionArray(TransitionArray *array);

void appendTransitionArray(TransitionArray *array, Transition value);

void freeTransitionArray(TransitionArray *array);

#endif //THIRD_PRACTICE_TRANSITION_H

//
// Created by Angel Miranda on 11/11/24.
//

#ifndef THIRD_PRACTICE_DETERMINIST_H
#define THIRD_PRACTICE_DETERMINIST_H

#include <stdlib.h>
#include "int_array.h"
#include "automaton.h"
#include "transition.h"

void determinist_export_automaton(Automaton *automaton);

typedef struct {
    int *states;
    int size;
} State;

int *determinist_get_transitions(Automaton *automaton, int state, char symb, int *transitions_size);

void determinist_init_states_automaton(IntArray states, State *all_states);

void determinist_append_states(State *origin, int *new_transitions, int transitions_size);

void determinist_sort_state(int *states, int size);

int determinist_equals(State *a, State *b);

int determinist_get_index(State *origin, State *new_states);

void determinist_conversion(Automaton *automaton);

#endif //THIRD_PRACTICE_DETERMINIST_H

//
// Created by Angel Miranda on 29/10/24.
//

#ifndef THIRD_PRACTICE_AUTOMATON_H
#define THIRD_PRACTICE_AUTOMATON_H

#include "char_array.h"
#include "int_array.h"
#include "string.h"
#include "transition.h"

typedef struct {
    IntArray states;
    CharArray alphabet;
    int start_state;
    IntArray final_states;
    TransitionArray transitions;
} Automaton;

void initAutomaton(Automaton *automaton);

void freeAutomaton(Automaton *automaton);

Automaton readAutomatonFromFile(const char *filename);

void printAutomaton(Automaton automaton);

int isFinalState(Automaton *automaton, int state);

int isValidState(Automaton *automaton, int state);

int isValidSymbol(Automaton *automaton, char symbol);

int validate(Automaton automaton, char *string, IntArray *path);

int validate_recursive(Automaton *automaton, int current_state, char *string, int position, IntArray *path);

#endif //THIRD_PRACTICE_AUTOMATON_H

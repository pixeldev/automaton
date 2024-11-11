//
// Created by Angel Miranda on 29/10/24.
//

#include "automaton.h"

void initAutomaton(Automaton *automaton) {
    initIntArray(&automaton->states);
    initCharArray(&automaton->alphabet);
    automaton->start_state = -1;
    initIntArray(&automaton->final_states);
    initTransitionArray(&automaton->transitions);
}

void freeAutomaton(Automaton *automaton) {
    freeIntArray(&automaton->states);
    freeCharArray(&automaton->alphabet);
    freeIntArray(&automaton->final_states);
    freeTransitionArray(&automaton->transitions);
}

Automaton readAutomatonFromFile(const char *filename) {
    Automaton automaton;
    initAutomaton(&automaton);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    char line[256];
    size_t line_number = 0;
    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);
        line_number++;
        char tokens[64][64];
        size_t num_tokens = split_line(line, tokens);
        if (line_number == 1) {
            // Primera línea: estados
            for (size_t i = 0; i < num_tokens; i++) {
                int state = string_to_int(tokens[i]);
                appendIntArray(&automaton.states, state);
            }
        } else if (line_number == 2) {
            // Segunda línea: alfabeto
            for (size_t i = 0; i < num_tokens; i++) {
                appendCharArray(&automaton.alphabet, tokens[i][0]);
            }
        } else if (line_number == 3) {
            // Tercera línea: estado inicial
            automaton.start_state = string_to_int(tokens[0]);
        } else if (line_number == 4) {
            // Cuarta línea: estados finales
            for (size_t i = 0; i < num_tokens; i++) {
                int state = string_to_int(tokens[i]);
                appendIntArray(&automaton.final_states, state);
            }
        } else {
            // Transiciones
            if (num_tokens >= 3) {
                int from_state = string_to_int(tokens[0]);
                if (!isValidState(&automaton, from_state)) {
                    printf("Error: estado %d no es válido en la línea %zu.\n", from_state, line_number);
                    exit(1);
                }
                char input_symbol = tokens[1][0];
                if (!isValidSymbol(&automaton, input_symbol)) {
                    printf("Error: símbolo %c no es válido en la línea %zu.\n", input_symbol, line_number);
                    exit(1);
                }
                int to_state = string_to_int(tokens[2]);
                if (!isValidState(&automaton, to_state)) {
                    printf("Error: estado %d no es válido en la línea %zu.\n", to_state, line_number);
                    exit(1);
                }
                Transition t;
                t.from_state = from_state;
                t.input_symbol = input_symbol;
                t.to_state = to_state;
                appendTransitionArray(&automaton.transitions, t);
            }
        }
    }
    fclose(file);
    return automaton;
}

void printAutomaton(Automaton automaton) {
    size_t i;
    printf("-=- Estados -=-\n");
    for (i = 0; i < automaton.states.size; i++) {
        printf("q%d ", automaton.states.data[i]);
    }
    printf("\n-=- Alfabeto -=-\n");
    for (i = 0; i < automaton.alphabet.size; i++) {
        printf("%c ", automaton.alphabet.data[i]);
    }
    printf("\n-=- Estado inicial -=-\n");
    printf("q%d\n", automaton.start_state);
    printf("-=- Estados finales -=-\n");
    for (i = 0; i < automaton.final_states.size; i++) {
        printf("q%d ", automaton.final_states.data[i]);
    }
    printf("\n-=- Transiciones -=-\n");
    for (i = 0; i < automaton.transitions.size; i++) {
        Transition t = automaton.transitions.data[i];
        if (t.to_state == automaton.start_state) {
            printf("→ ");
        } else if (isFinalState(&automaton, t.to_state)) {
            printf("* ");
        }
        printf("q%d(%c) -> q%d\n", t.from_state, t.input_symbol, t.to_state);
    }
}

int isFinalState(Automaton *automaton, int state) {
    size_t i;
    for (i = 0; i < automaton->final_states.size; i++) {
        if (automaton->final_states.data[i] == state) {
            return 1;
        }
    }
    return 0;
}

int isValidState(Automaton *automaton, int state) {
    size_t i;
    for (i = 0; i < automaton->states.size; i++) {
        if (automaton->states.data[i] == state) {
            return 1;
        }
    }
    return 0;
}

int isValidSymbol(Automaton *automaton, char symbol) {
    size_t i;
    for (i = 0; i < automaton->alphabet.size; i++) {
        if (automaton->alphabet.data[i] == symbol) {
            return 1;
        }
    }
    return 0;
}

int validate(Automaton automaton, char *string, IntArray *path) {
    return validate_recursive(&automaton, automaton.start_state, string, 0, path);
}

void printPath(char *string, IntArray *path) {
    size_t i;
    printf("-=- Camino encontrado -=-\n");
    for (i = 0; i < path->size; i++) {
        printf("q%d", path->data[i]);
        if (i < path->size - 1) {
            printf("(%c) -> ", string[i]);
        }
    }
    printf("\n");
}

int validate_recursive(Automaton *automaton, int current_state, char *string, int position, IntArray *path) {
    size_t str_len = string_length(string);
    int found = 0;

    appendIntArray(path, current_state);

    if (position == str_len) {
        if (isFinalState(automaton, current_state)) {
            printPath(string, path);
            found = 1;
        }
    } else {
        char current_symbol = string[position];

        size_t i;
        for (i = 0; i < automaton->transitions.size; i++) {
            Transition t = automaton->transitions.data[i];
            if (t.from_state == current_state && t.input_symbol == current_symbol) {
                if (validate_recursive(automaton, t.to_state, string, position + 1, path)) {
                    found = 1;
                }
            }
        }
    }

    popIntArray(path);

    return found;
}
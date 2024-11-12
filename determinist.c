#include <stdlib.h>
#include "int_array.h"
#include "automaton.h"
#include "transition.h"

void exportAutomaton(Automaton* automaton) {
    FILE *archivo = fopen("automaton.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < automaton->states.size; i++) {
        fprintf(archivo, "%d", automaton->states.data[i]);
        if (i < automaton->states.size - 1) fprintf(archivo, ",");
    }
    fprintf(archivo, "\n");

    for (int i = 0; i < automaton->alphabet.size; i++) {
        fprintf(archivo, "%c", automaton->alphabet.data[i]);
        if (i < automaton->alphabet.size - 1) fprintf(archivo, ",");
    }
    fprintf(archivo, "\n");

    fprintf(archivo, "%d\n", automaton->start_state);

    // Exportar los estados finales (F)
    for (int i = 0; i < automaton->final_states.size; i++) {
        fprintf(archivo, "%d", automaton->final_states.data[i]);
        if (i < automaton->final_states.size - 1) fprintf(archivo, ",");
    }
    fprintf(archivo, "\n");

    // Exportar las transiciones (qi, sigma, qo)
    for (int i = 0; i < automaton->transitions.size; i++) {
        fprintf(archivo, "%d,%c,%d\n", automaton->transitions.data[i].from_state, automaton->transitions.data[i].input_symbol, automaton->transitions.data[i].to_state);
    }

    // Cerrar el archivo
    fclose(archivo);
}



typedef struct new_state
{
    int *states;
    int size;
}State;

int* getTransitions(Automaton* automaton, int state, char symb, int* transitions_size) {
    int* transitions = (int*)malloc( (1<<automaton->states.size)*(automaton->alphabet.size)* sizeof(int));
    *transitions_size = 0;
    for (int i = 0; i < automaton->transitions.size; i++) {
        if (automaton->transitions.data[i].from_state == state && automaton->transitions.data[i].input_symbol== symb) {
            transitions[(*transitions_size)++] =  automaton->transitions.data[i].to_state;
        }
    }
    return transitions;
}

void initStatesAutomatonDet(IntArray states, State* all_states ) {
    all_states = (State*) malloc((1 << states.size)*sizeof(State));
    all_states->size = 1 << states.size;

    for (int i = 0; i < all_states->size; i++) {
        all_states[i].states = (int*) malloc(states.size * sizeof(int));  
        int size = 0;
        for (int j = 0; j < states.size; j++) {
            if (i & (1 << j)) {
                all_states[i].states[size] = states.data[j];
                size++;
            }
        }
        all_states[i].size = size;
    }
}

void append_states(State* origin, int* new_transitions, int transitions_size){
    int* new_state = (int*) malloc((origin->size + transitions_size) * sizeof(int));
    for (int i = 0; i < origin->size; i++) {
        new_state[i] = origin->states[i];
    }
    for (int i = 0; i < transitions_size; i++) {
        new_state[i + origin->size] = new_transitions[i];
    }

    free(origin->states); 
    origin->states = new_state;
    origin->size += transitions_size;
}

void sort_State(int* states, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (states[i] > states[j]) {
                int temp = states[i];
                states[i] = states[j];
                states[j] = temp;
            }
        }
    }
}

int equals(State* a, State* b) {
    if (a->size != b->size) return 0;

    int* state_A = (int*) malloc(a->size * sizeof(int));
    int* state_B = (int*) malloc(b->size * sizeof(int));

    for (int i = 0; i < a->size; i++) {
        state_A[i] = a->states[i];
        state_B[i] = b->states[i];
    }

    sort_State(state_A, a->size);
    sort_State(state_B, b->size);

    for (int i = 0; i < a->size; i++) {
        if (state_A[i] != state_B[i]) {
            free(state_A);
            free(state_B);
            return 0;
        }
    }

    free(state_A);
    free(state_B);
    return 1;
}

int getIndex(State* origin, State* new_states) {
    for (int i = 0; i < new_states->size; i++) {
        if (sonIguales(origin, &new_states[i])) {
            return i;
        }
    }
    return -1;
}

void toDeterminist(Automaton* automaton) {
    State *new_states;
    
    Automaton automaton_det;
    initAutomaton(&automaton_det);


    initStatesAutomatonDet(automaton->states, new_states);

    int *new_states_automaton = (int*) malloc(new_states->size*sizeof(int));
    for(int i=0; i< new_states->size;i++){
        new_states_automaton[i]= i;
        printf("%d ->", i );
        for(int j=0; j<new_states[i].size;j++){
            printf(" %d ", new_states[i].states[i]);
            if (j < new_states[i].size - 1) printf(", ");
        }
        printf("\n");
    }
    automaton_det.states.data = new_states_automaton;
    automaton_det.states.size = new_states->size;

    int* new_final_states = (int*) malloc(new_states->size * sizeof(int));
    int index = 0;

    for (int i = 0; i < new_states->size; i++) {
        for (int j = 0; j < new_states[i].size; j++) {
            for (int k = 0; k < automaton->final_states.size; k++) {
                if (new_states[i].states[j] == automaton->final_states.data[k]) {
                    new_final_states[index] = i;
                    index++;
                    break;
                }
            }
        }
    }
    automaton_det.final_states.data = new_final_states;
    automaton_det.final_states.size = index+1;

    State aux ;
    aux.states = (int*) malloc(sizeof(int));
    aux.states = automaton->start_state;
    aux.size =1;

    automaton_det.start_state = getIndex(&aux, new_states);
    
    

    Transition* new_transitions = (Transition*) malloc(new_states->size * automaton->alphabet.size * sizeof(Transition));
    index = 0;

    State aux_2;
    aux_2.states = NULL;
    aux_2.size = 0;

    for (int i = 0; i < new_states->size; i++) {
        for (int j = 0; j < automaton->alphabet.size; j++) {
            aux_2.size = 0;
            free(aux_2.states);  
            aux_2.states = NULL;

            for (int k = 0; k < new_states[i].size; k++) {
                int transitions_size;
                int* aux_transitions = getTransitions(automaton, new_states[i].states[k], automaton->alphabet.data[j], &transitions_size);
                append_States(&aux_2, aux_transitions, transitions_size);
                free(aux_transitions);
            }

            int output = getIndex(&aux_2, new_states);
            new_transitions[index].from_state=i;
            new_transitions[index].input_symbol = automaton->alphabet.data[j];
            new_transitions[index].from_state = output;
            index++;
        }
    }

    
    automaton_det.alphabet = automaton->alphabet;
    
    
    automaton_det.transitions.data = new_transitions;
    automaton_det.transitions.size = index+1;

    exportAutomaton(&automaton_det);

    

    freeAutomaton(automaton);
    freeAutomaton(&automaton_det);
}

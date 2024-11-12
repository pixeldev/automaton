#include "automaton.h"
#include "determinist.c"

int main() {
    char *string = NULL;
    size_t n = 0;

    printf("Ingrese la ruta del archivo\n>> ");
    getline(&string, &n, stdin);
    string[string_length(string) - 1] = '\0';

    Automaton automaton = readAutomatonFromFile(string);
    printf("Automata leído correctamente.\n");

    toDeterminist(&automaton);
    
    return 0;
}
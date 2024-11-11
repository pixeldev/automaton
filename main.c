#include "automaton.h"

int main() {
    char *string = nullptr;
    size_t n = 0;

    printf("Ingrese la ruta del archivo\n>> ");
    getline(&string, &n, stdin);
    string[string_length(string) - 1] = '\0';

    Automaton automaton = readAutomatonFromFile(string);
    printf("Automata leído correctamente.\n");

    int option = 0;

    while (option != 3) {
        free(string);
        string = nullptr;
        n = 0;

        printf("Selecciona una opción:\n");
        printf("1. Imprimir automata\n");
        printf("2. Validar cadena\n");
        printf("3. Salir\n");
        printf(">> ");
        scanf("%d", &option);

        while (getchar() != '\n');

        switch (option) {
            case 1: {
                printAutomaton(automaton);
                break;
            }
            case 2: {
                IntArray path;
                initIntArray(&path);
                printf("Ingrese una cadena\n>> ");
                getline(&string, &n, stdin);
                string[string_length(string) - 1] = '\0';
                printf("%s\n", string);
                if (!validate(automaton, string, &path)) {
                    printf("Cadena inválida\n");
                }
                freeIntArray(&path);
                break;
            }
            case 3:
                break;
            default:
                printf("Opción inválida\n");
                break;
        }
    }

    freeAutomaton(&automaton);
    return 0;
}
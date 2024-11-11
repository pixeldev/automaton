//
// Created by Angel Miranda on 29/10/24.
//

#include "string.h"

size_t string_length(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int string_to_int(const char *str) {
    int num = 0;
    int i = 0;
    int negativo = 0;
    if (str[0] == '-') {
        negativo = 1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    if (negativo) {
        num = -num;
    }
    return num;
}

void trim_newline(char *str) {
    size_t len = string_length(str);
    if (len == 0)
        return;
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

size_t split_line(const char *line, char tokens[][64]) {
    size_t num_tokens = 0;
    size_t i = 0;
    size_t token_start = 0;
    size_t token_length = 0;

    while (1) {
        char c = line[i];
        if (c == ',' || c == '\n' || c == '\0') {
            if (token_length > 0) {
                // Copiar el token
                size_t j;
                for (j = 0; j < token_length && j < 63; j++) {
                    tokens[num_tokens][j] = line[token_start + j];
                }
                tokens[num_tokens][j] = '\0';
                num_tokens++;
                token_length = 0;
            }
            if (c == '\0' || c == '\n') {
                break;
            }
            token_start = i + 1;
        } else {
            token_length++;
        }
        i++;
    }
    return num_tokens;
}

//
// Created by Angel Miranda on 29/10/24.
//

#ifndef THIRD_PRACTICE_STRING_H
#define THIRD_PRACTICE_STRING_H

#include <stdlib.h>

size_t string_length(const char *str);

int string_to_int(const char *str);

void trim_newline(char *str);

size_t split_line(const char *line, char tokens[][64]);

#endif //THIRD_PRACTICE_STRING_H

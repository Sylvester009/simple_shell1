#include "main.h"

void tokenize(char *input, char *args[]) {
    int i = 0;
    char *token = input;

    while (*token != '\0') {
        while (*token == ' ' || *token == '\t' || *token == '\n') {
            *token = '\0';
            token++;
        }

        args[i++] = token;

        while (*token != '\0' && *token != ' ' && *token != '\t' && *token != '\n') {
            token++;
        }
    }

    args[i] = NULL;
}

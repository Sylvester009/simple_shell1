#include "main.h"

void tokenize(char *input, char *args[]) {
    int i = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && i < MAX_SIZE - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    args[i] = NULL;
}

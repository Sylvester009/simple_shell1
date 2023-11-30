#include "main.h"

void tokenize_input(char *input, char *args[])
{
    char *token = strtok(input, " ");
    int i = 0;

    /**Populate the arguments array*/
    while (token != NULL && i < MAX_SIZE - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
}

include "main.h"

void tokenize(char *input, char *args[])
{
    /** Use strtok to split the input into tokens*/
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < MAX_SIZE - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
}

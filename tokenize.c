#include "main.h"

void tokenize(char *input, char *args[])
{
    int i = 0;
    int start = 0;
    int end = 0;
    int token_length = 0;

    while (input[start] != '\0' && i < MAX_SIZE - 1)
    {
        while (input[start] == ' ' || input[start] == '\t')
        {
            start++;
        }

        /** Find the end of the current token*/
        end = start;
        while (input[end] != '\0' && input[end] != ' ' && input[end] != '\t')
        {
            end++;
        }

        /** Extract the token and add it to args*/
        token_length = end - start;
        args[i] = malloc(token_length + 1);
        strncpy(args[i], input + start, token_length);
        args[i][token_length] = '\0';

        /** Move to the next token*/
        start = end;
        i++;
    }

    args[i] = NULL;
}

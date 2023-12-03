#include "main.h"

void handle_env()
{
    extern char **environ;

    char **env = environ;

    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}


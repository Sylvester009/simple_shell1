#include "main.h"

void handle_env()
{
    extern char **environ;

    char **env = environ;

    for (*env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}

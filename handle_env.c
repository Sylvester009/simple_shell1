#include "main.h"

void handle_env()
{
    extern char **environ;

    for (char **env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}

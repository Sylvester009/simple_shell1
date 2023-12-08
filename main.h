#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 1024

void tokenize(char *input, char *args[]);
int exit_shell();
void handle_env();
char *my_getline(void);
char **get_environment(inform_t *inform);
int _unsetenv(inform_t *inform, char *var);
int _setenv(inform_t *inform, char *var, char *value);

#endif

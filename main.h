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
void handle_exit(int status);
void handle_env();
char *my_getline(void);

#endif

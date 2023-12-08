#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 1024

typedef struct list_node {
    char *str;                 
    struct list_node *next;    
} inform_t;

void tokenize(char *input, char *args[]);
int exit_shell();
void handle_env();
char *my_getline(void);
int _unsetenv(inform_t *inform, char *var);
int _setenv(inform_t *inform, char *var, char *value);

list_t *create_node(char *str);
void add_node(list_t **head, char *str);
void print_list(list_t *head);
void free_list(list_t *head);

#endif

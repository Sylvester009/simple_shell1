#include "main.h"

list_t *create_node(char *str) {
    list_t *new_node;
    if (!(new_node = (list_t *)malloc(sizeof(list_t)))) {
        exit(EXIT_FAILURE);
    }
    new_node->str = strdup(str);
    new_node->next = NULL;
    return new_node;
}

void add_node(list_t **head, char *str) {
    list_t *new_node = create_node(str);
    if (*head == NULL) {
        *head = new_node;
    } else {
        list_t *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void print_list(list_t *head) {
    while (head != NULL) {
        printf("%s\n", head->str);
        head = head->next;
    }
}

void free_list(list_t *head) {
    while (head != NULL) {
        list_t *temp = head;
        head = head->next;
        free(temp->str);
        free(temp);
    }
}

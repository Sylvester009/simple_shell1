#include "main.h"

char *my_getline(void) {
    static char buffer[MAX_SIZE];
    static size_t buffer_index = 0;
    static size_t buffer_size = 0;

    size_t line_length = 0;

    char *line;

    /**Check if the buffer needs to be filled*/
    if (buffer_index >= buffer_size) {
        buffer_size = read(STDIN_FILENO, buffer, MAX_SIZE);

        if (buffer_size <= 0) {
            return NULL;
        }

        buffer_index = 0;
    }

    
    while (buffer_index + line_length < buffer_size && buffer[buffer_index + line_length] != '\n') {
        line_length++;
    }

    line = malloc(line_length + 1);
    if (line == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    
    memcpy(line, buffer + buffer_index, line_length);
    line[line_length] = '\0';

    
    buffer_index += line_length + 1;

    return (line);
}

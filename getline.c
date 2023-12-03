#include "main.h"

char *my_getline(void) {
    static char buffer[MAX_SIZE];
    size_t buffer_index = 0;
    size_t buffer_size = 0;
    size_t line_length = 0;

     char *line = malloc(line_length + 1);

    /** Check if buffer needs to be filled */
    if (buffer_index >= buffer_size) {
        buffer_size = fread(buffer, 1, MAX_SIZE, stdin);
        if (buffer_size == 0) {
            /** End of file or an error occurred*/
            return (NULL);
        }
        buffer_index = 0;
    }

    /** Find the length of the line*/
    while (buffer_index + line_length < buffer_size && buffer[buffer_index + line_length] != '\n') {
        line_length++;
    }

    /** Allocate memory for the line*/
    if (line == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* Copy the line from the buffer to the allocated memory*/
    memcpy(line, buffer + buffer_index, line_length);
    line[line_length] = '\0';

    /** Move the buffer index to the next line*/
    buffer_index += line_length + 1;

    return (line);
}

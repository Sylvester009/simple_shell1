#include "main.h"

int exit_shell() {
    int exit_status;
    int input_valid;

    do {
        input_valid = 1;  /* Assume input is valid */

        /** Get the exit status from the user*/
        printf("Enter exit status: ");
        fflush(stdout);

        char *exit_input = my_getline();

        if (!exit_input) {
            printf("\n");
            break;
        }

        if (exit_input[0] == '\0') {
            /** If no exit status provided, exit with default status*/
            exit(EXIT_SUCCESS);
        }

        exit_status = str_integer(exit_input);
        if (exit_status == -1) {
            printf("Illegal number: %s\n", exit_input);
            input_valid = 0;  /* Invalid input, repeat the loop */
        } else {
            /** Exit with the specified status*/
            exit(exit_status);
        }

        free(exit_input);

    } while (!input_valid);

    return -2;
}

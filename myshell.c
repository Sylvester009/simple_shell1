#include "main.h"

int main(void) {
    char *input;
    size_t len;
    pid_t pid;
    int status;

    char *args[MAX_SIZE]; /** Assuming a maximum number of arguments */

    char *env[] = {NULL};

    while (1) {
        printf("$ ");  // Print prompt
        fflush(stdout);

        input = my_getline();

        if (input == NULL) {
            printf("\n");
            break;
        }

        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /** Child process */
            tokenize(input, args);
            execve(args[0], args, env);

            /** If execve fails */
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            /** Parent process */
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                /** Child process terminated normally */
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                /** Child process terminated by a signal */
                printf("Child process terminated by signal %d\n", WTERMSIG(status));
            }
        }

        // Free the memory allocated by my_getline
        free(input);
    }

    return 0;
}

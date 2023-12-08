#include "main.h"

void prompt();

int main(void) {
    char *input = NULL;
    size_t len;
    pid_t pid;
    int status;
    int exit_stats;

    char *args[MAX_SIZE];
    char *env[] = {NULL};

    while (1) {
        prompt();

        input = my_getline();

        if (input == NULL) {
            free(input);
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
            free(input);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /** Child process */
            tokenize(input, args);

            if (strcmp(args[0], "exit") == 0) {
                exit_stats = exit_shell();
                exit(exit_stats);
            } else if (strcmp(args[0], "env") == 0) {
                handle_env();
            } else if (strcmp(args[0], "setenv") == 0) {
                if (args[1] && args[2]) {
                    _setenv(&inform, args[1], args[2]);
                } else {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                }
                free(input);
                exit(EXIT_SUCCESS);  // Exit the child process after setenv
            } else if (strcmp(args[0], "unsetenv") == 0) {
                if (args[1]) {
                    _unsetenv(&inform, args[1]);
                } else {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                }
                free(input);
                exit(EXIT_SUCCESS);  // Exit the child process after unsetenv
            }

            execve(args[0], args, env);

            /** If execve fails */
            perror("execve");
            free(input);
            exit(EXIT_FAILURE);
        } else {
            /** Parent process */
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                /** Child process terminated normally */
                printf("%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                /** Child process terminated by a signal */
                printf(" %d\n", WTERMSIG(status));
            }
        }
    }

    free(input);
    return 0;
}

void prompt() {
    printf("$ ");
    fflush(stdout);
}

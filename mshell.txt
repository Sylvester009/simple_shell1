#include "main.h"

void prompt();

int search_path(const char *command, char *full_path) {
char *token;
    
    /* Get the value of the PATH environment variable*/
    char *path = getenv("PATH");
    if (path == NULL) {
        perror("getenv");
        return -1;
    }

    /* Tokenize the PATH variable to get individual directories*/
    token = strtok(path, ":");
    while (token != NULL) {
        /* Construct the full path of the command*/
        snprintf(full_path, MAX_SIZE, "%s/%s", token, command);

        /* Check if the command exists at the current path*/
        if (access(full_path, X_OK) == 0) {
            return 0; 
        }

        /* Move to the next directory in PATH*/
        token = strtok(NULL, ":");
    }

    return (-1);  
}

int main(void) {
    char *input = NULL;
    size_t len;
    pid_t pid;
    int status;

    extern char **environ;

    char *args[MAX_SIZE];
    char full_path[MAX_SIZE];

    while (1) {
        prompt();

        if (getline(&input, &len, stdin) == -1) {
            free(input);
            printf("\n");
            break;
        }

        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        
        if (strcmp(input, "exit") == 0) {
            free(input);
            exit_shell();
        }

        
        if (search_path(input, full_path) == 0) {
            pid = fork();

            if (pid == -1) {
                perror("fork");
                free(input);
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                /* Child process*/
                tokenize(full_path, args);

                execve(args[0], args, environ);

                /* If execve fails*/
                perror("execve");
                free(input);
                exit(EXIT_FAILURE);
            } else {
                /* Parent process*/
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    printf("%d\n", WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf(" %d\n", WTERMSIG(status));
                }
            }
        } else {
            /*Command not found in PATH*/
            printf("Command not found: %s\n", input);
        }
    }

    free(input);
    return 0;
}

void prompt() {
    printf("$ ");
    fflush(stdout);
}

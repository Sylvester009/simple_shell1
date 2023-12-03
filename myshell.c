#include "main.h"

void prompt();
void tokenize_input(char *input, char *args[]);

int main(void)
{
    char input[MAX_SIZE];
    size_t len;
    pid_t pid;
    int status;

    char *args[MAX_SIZE]; /** Assuming a maximum number of arguments */

    char *env[] = {NULL};

    while (1)
    {
        prompt();

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /** Child process */
            tokenize_input(input, args);

            execve(args[0], args, env);

            /** If execve fails */
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            /** Parent process */
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                /** Child process terminated normally */
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                /** Child process terminated by a signal */
                printf("Child process terminated by signal %d\n", WTERMSIG(status));
            }
        }
    }

    return 0;
}

void prompt()
{
    printf("$ ");
    fflush(stdout);
}

void tokenize_input(char *input, char *args[])
{
    /** Use strtok to split the input into tokens */
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL; /** Set the last element to NULL to terminate the args array*/
}

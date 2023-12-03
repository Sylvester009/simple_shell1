#include "main.h"

void prompt();

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
            tokenize(input, args);

            if (strcmp(args[0], "exit") == 0)
            {
                handle_exit(0);
            }
            else (strcmp(args[0], "env") == 0)
            {
                handle_env();
            }

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
                printf("%d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                /** Child process terminated by a signal */
                printf(" %d\n", WTERMSIG(status));
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

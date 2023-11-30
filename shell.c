#include "main.h"

void display_prompt();

int main(void)
{
    char input[MAX_SIZE];
    size_t len;
    pid_t pid;
    int status;

    while (1)
    {
        display_prompt();

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
            char *args[2];
            args[0] = input;
            args[1] = NULL;
            /** Split the command into arguments*/
            char *env[] = {NULL};

            /** Specify the environment*/
            
            execve(input, args, env);

            /** If execve fails*/
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
        {
            /** Parent process*/
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                /** Child process terminated normally*/
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                /**Child process terminated by a signal*/
                printf("Child process terminated by signal %d\n", WTERMSIG(status));
            }
        }
    }

    return 0;
}

void display_prompt()
{
    printf("$ ");
    fflush(stdout);
}

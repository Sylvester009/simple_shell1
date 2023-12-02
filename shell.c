#include "main.h"

void d_prompt();

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
        d_prompt();

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

        if (strcmp(input, "/bin/ls") == 0)
        {
            pid = fork();

            if (pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                /** Child process */
                execve("/bin/ls", args, env);

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
        else if (access(input, X_OK) == 0)
        {
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
        else
        {
            printf(" No such file or directory s\n", input);
        }
    }

    return 0;
}

void d_prompt()
{
    printf("$ ");
    fflush(stdout);
}

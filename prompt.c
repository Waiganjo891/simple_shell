#include "Functions.h"

void prompt(char **av, char **env)
{
    char *string = NULL;
    int i, j, status;
    size_t n = 0;
    ssize_t num_char;
    char *argv[FUNCTION_H];
    pid_t child_pid;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("Shell$ ");
        num_char = getline(&string, &n, stdin);
        if (num_char == -1)
        {
            free(string);
            exit(EXIT_FAILURE);
        }
        i = 0;
        while (string[i])
        {
            if (string[i] == '\n')
                string[i] = 0;
            i++;
        }
        j = 0;
        argv[j] = strtok(string, " ");
	if (argv[j] == NULL)
	{
		continue;
	}
        while (argv[j])
        {
            argv[++j] = strtok(NULL, " ");
        }
	if (strcmp(argv[0], "exit") == 0)
        {
            free(string);
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argv[0], "env") == 0)
        {
            print_environment(env);
        }
	else if (access(argv[0], X_OK) == 0)
        {
            child_pid = fork();
            if (child_pid == -1)
            {
                free(string);
                exit(EXIT_FAILURE);
            }
	    else if (child_pid == 0)
            {
                if (execve(argv[0], argv, env) == -1)
                {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            }
            else
                wait(&status);
        }
        else
        {
            printf("%s: No such file or directory\n", av[0]);
        }
    }
}

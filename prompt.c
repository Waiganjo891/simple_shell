#include "shell.h"
/**
 * prompt - A void
 * @av: A character
 * @env: Another character
 */
void prompt(char **av, char **env)
{
	char *string = NULL;
	int i, j, a, status;
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
		while (argv[j])
		{
			argv[++j] = strtok(NULL, " ");
		{
			if (strcmp(argv[0], "env") == 0)
			{
				a = 0;
				while (env[a] != NULL)
				{
					printf("%s\n", env[a]);
					a++;
				}
			}
			else if (access(argv[0], X_OK) == 0)
			{
				child_pid = fork();
				if (child_pid == -1)
				{
					free(string);
					exit(EXIT_FAILURE);
				}
				if (child_pid == 0)
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

#include "Functions.h"
/**
 * execute_command - A void
 * @argv: A character
 * @env: Another character
 */
void execute_command(char **argv, char **env)
{
	int status;
	char *string = NULL;
	pid_t child_pid;

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
	{
		wait(&status);
	}
}

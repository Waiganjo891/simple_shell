#include "Functions.h"
/**
 * execute_command - A void
 * @argv: A character
 * @env: Another character
 */
void execute_command(char **argv, char **env)
{
	int status, shlvl_value;
	char *string = NULL, *shlvl;
	char shlvl_str[100];
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		free(string);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (strcmp(argv[0], "bash") == 0 || strcmp(argv[0], "sh") == 0)
		{
			shlvl = getenv("SHLVL");
			shlvl_value = shlvl ? atoi(shlvl) : 0;
			sprintf(shlvl_str, "%d", shlvl_value + 1);
			setenv("SHLVL", shlvl_str, 1);
		}
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

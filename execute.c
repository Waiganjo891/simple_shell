#include "Functions.h"
/**
 * execute_absolute_path - A void
 * @argv: A character
 * @env: Another character
 */
void execute_absolute_path(char **argv, char **env)
{
	pid_t child_pid;
	int status;

	if (access(argv[0], X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
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
		{
			wait(&status);
		}
	}
	else
	{
		printf("%s: No such file or directory\n", argv[0]);
	}
}
/**
 * execute_relative_path - A void
 * @argv: A character
 * @env: Another character
 */
void execute_relative_path(char **argv, char **env)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *directory = strtok(path_copy, ":");
	char filepath[1024];
	pid_t child_pid;
	int status;

	while (directory)
	{
		sprintf(filepath, "%s/%s", directory, argv[0]);
		if (access(filepath, X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (child_pid == 0)
			{
				if (execve(filepath, argv, env) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				wait(&status);
			}
			break;
		}
		directory = strtok(NULL, ":");
	}
	free(path_copy);

	if (!directory)
	{
		printf("%s: No such file or directory\n", argv[0]);
	}
}

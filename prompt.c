#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - An integer
 * Return: Always (0)
 */
int main(void)
{
	char command[1024], *word, *args[1024];
	pid_t child_pid;
	char *env_args[] = {"/bin/bash", (char *)0};
	int i = 0, status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;
		command[strcspn(command, "\n")] = 0;
		word = strtok(command, " ");
		while (word != NULL)
		{
			args[i] = word;
			word = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		else if (child_pid == 0)
		{
			if (execve(args[0], args, env_args) == -1)
			{
				perror("Error: ");
				return (1);
			}
		}
		else
			wait(&status);
		i = 0;
	}
	return (0);
}

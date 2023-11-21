#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
/**
 * main - An integer
 * Return: Always (0)
 */
int main(void)
{
	char command[1024], *word, *args[1024];
	pid_t child_pid;
	char *env_args[] = {"/bin/bash", (char *)0};
	struct stat file_stat;
	int i = 0, status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}
		command[strcspn(command, "\n")] = 0;
		if (strlen(command) == 0)
		{
			continue;
		}
		if (strcmp(command, "stat") == 0)
		{
			printf("Please provide a file path for the stat command.\n");
			continue;
		}
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
			if (strcmp(args[0], "stat") == 0)
			{
				if (args[1] == NULL)
				{
					printf("Please provide a file path for the stat command.\n");
					exit(1);
				}
				if (stat(args[1], &file_stat) == -1)
				{
					perror("Error: ");
					exit(1);
				}
				printf("File size: %ld bytes\n", file_stat.st_size);
				exit(0);
			}
			else
			{
				if (execve(args[0], args, env_args) == -1)
				{
					perror("Error: ");
					return (1);
				}
			}
		}
		else
			wait(&status);
		i = 0;
	}
	return (0);
}

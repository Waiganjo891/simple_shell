#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	char command[1024];
	char *word;
	char *args[100];
	pid_t pid;
	char *env_args[] = {"/bin/bash", (char *)0};
	struct stat file_status;
	int i = 0;

	printf("$ ");
	fgets(command, sizeof(command), stdin);
	command[strcspn(command, "\n")] = 0;
	word = strtok(command, " ");
	while (word != NULL)
	{
		args[i] = word;
		word = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	pid = fork();

	if (pid == -1)
	{
		perror("Error forking process");
		return (1);
	}
	else if (pid == 0)
	{
		if (stat(args[0], &file_status) == -1)
		{
			perror("Error getting file status");
			return (1);
		}
		if (execve(args[0], args, env_args) == -1)
		{
			perror("Error executing command");
			return (1);
		}
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

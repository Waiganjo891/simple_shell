#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char command[1024];
	char *word;
	char *args[100];
	pid_t pid;
	char *env_args[] = {"/bin/bash", (char *)0};
	int status;
	int i = 0;

	while (1)
	{
		printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}
		command[strcspn(command, "\n")] = 0;
		word = strtok(command, " ");
		while (word != NULL)
		{
			args[i] = strdup(word);
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
			if (execve(args[0], args, env_args) == -1)
			{
				perror("Error executing command");
				exit(1);
			}
			for (int j = 0; args[j] != NULL; j++)
			{
				free(args[j]);
			}
			exit(0);
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("Error waiting for child process");
				return (1);
			}
		}
		for (int j = 0; args[j] != NULL; j++)
		{
			free(args[j]);
		}
		i = 0;
	}
	return (0);
}

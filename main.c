#include "functions.h"
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
		{
			break;
		}
		command[strcspn(command, "\n")] = 0;
		if (strlen(command) == 0)
		{
			continue;
		}
		if (strcmp(command, "exit") == 0)
		{
			break;
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
			char *command_path = get_command_path(args[0]);
			if (command_path != NULL)
			{
				if (execve(args[0], args, env_args) == -1)
				{
					perror("Error: ");
					return (1);
				}
			}
			else
			{
				printf("Command not found: %s\n", args[0]);
				return (1);
			}
		}
		else
		{
			wait(&status);
		}
		i = 0;
	}
	return (0);
}

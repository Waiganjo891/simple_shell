#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * main - An integer
 * Return: Always (0);
 */
int main(void)
{
	char command[1024];
	char *word;
	char *args[100];
	char *env_args[] = {"/bin/bash", (char *)0};
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
			args[i] = word;
			word = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		if (execve(args[0], args, env_args) == -1)
		{
			perror("Error executing command");
			return (1);
		}
	}
	return (0);
}

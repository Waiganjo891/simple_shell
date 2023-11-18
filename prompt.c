#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
	char command[1024];
	char *word;
	char *args[100];
	char *env_args[] = {"/bin/bash", (char *)0};
	int i = 0;
	int status;
	pid_t pid;

	printf("$ ");
	fgets(command, sizeof(command), stdin);
	command[strcspn(command, "\n")] = 0;
	word = strtok(command, " ");
	while(word != NULL)
	{
		args[i] = word;
		printf("%s\n", word);
		word = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;

	pid = fork();
	if (pid < 0)
	{
		perror("Error forking");
		return (1);
	}
	else if (pid == 0)
	{
		if(execve(args[0], args, env_args) == -1)
		{
			perror("Error executing command");
			return (1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			printf("Child exited with status %d\n", WEXITSTATUS(status));
		}
	}
	return (0);
}

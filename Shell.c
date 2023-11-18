#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char command[1024];
	char *word;
	char *args[10];
	char *env_args[] = {"/bin/bash", (char *)0};
	int i = 0;
	pid_t pid;

	printf("$ ");
	fgets(command, sizeof(command), stdin);

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
	if(pid == 0)
	{
		execve(args[0], args, env_args);
	}
	else if(pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("Error forking");
	}
	return (0);
}

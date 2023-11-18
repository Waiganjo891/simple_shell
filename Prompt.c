
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	char command[1024];
	char *word;
	char *args[10];
	char *env_args[] = {"/bin/bash", (char *)0};
	int i = 0;

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
	execve(args[0], args, env_args);
	return 0;
}

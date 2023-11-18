#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char command[100];
	pid_t my_pid;

        my_pid = getpid();
        printf("%u\n", my_pid);

	printf("$ ");
	fgets(command, sizeof(command), stdin);
	printf("\n%s\n", command);

	return 0;
}

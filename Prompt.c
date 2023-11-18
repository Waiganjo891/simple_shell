#include <stdio.h>

int main(void)
{
	char command[1024];

	printf("$ ");
	fgets(command, sizeof(command), stdin);
	printf("\n%s\n", command);

	return (0);
}

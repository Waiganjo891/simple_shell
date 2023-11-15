#include "Functions.h"
/**
 * exit_command - A void
 * @argv: A character
 */
void exit_command(char **argv)
{
	char *string = NULL;
	int status;

	status = argv[1] ? atoi(argv[1]) : EXIT_SUCCESS;
	free(string);
	exit(status);
}

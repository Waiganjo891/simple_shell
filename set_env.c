#include "Functions.h"
/**
 * handle_setenv - A void
 * @argv: A character
 */
void handle_setenv(char **argv)
{
	if (argv[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
	else
	{
		if (setenv(argv[1], argv[2], 1) == -1)
		{
			perror("setenv");
		}
	}
}
/**
 * handle_unsetenv - A void
 * @argv: A character
 */
void handle_unsetenv(char **argv)
{
	if (argv[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
	else
	{
		if (unsetenv(argv[1]) == -1)
		{
			perror("unsetenv");
		}
	}
}

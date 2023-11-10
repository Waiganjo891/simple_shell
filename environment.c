#include "Functions.h"
/**
 * print_environment - A void
 * @env: A character
 */
void print_environment(char **env)
{
	unsigned int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

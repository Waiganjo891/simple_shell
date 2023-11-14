#include "Functions.h"
/**
 * handle_env - A void
 * @env: A character
 */
void handle_env(char **env)
{
	unsigned int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

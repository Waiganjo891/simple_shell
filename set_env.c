#include "Functions.h"
extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
	char **env = environ;
	char *this_env;
	char *new_env;
	int found = 0;

	while (*env != NULL)
	{
		this_env = *env;
		if (strncmp(this_env, name, strlen(name)) == 0 && this_env[strlen(name)] == '=')
		{
			found = 1;
			if (overwrite)
			{
				new_env = malloc(strlen(name) + strlen(value) + 2);
				sprintf(new_env, "%s=%s", name, value);
				*env = new_env;
			}
			break;
		}
		env++;
	}
	if (!found && overwrite)
	{
		new_env = malloc(strlen(name) + strlen(value) + 2);
		sprintf(new_env, "%s=%s", name, value);
		*env = new_env;
	}
	return 0;
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

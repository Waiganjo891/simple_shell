#include "Functions.h"
/**
 * tokenize_input - A void
 * @string: A character
 * @argv: Another character
 */
void tokenize_input(char *string, char *argv[])
{
	int j = 0;

	argv[j] = strtok(string, " ");
	if (argv[j] == NULL)
	{
		return;
	}
	while (argv[j])
	{
		argv[++j] = strtok(NULL, " ");
	}
}

/**
 * prompt - A void
 * @av: A character
 * @env: Another character
 */
void prompt(char **av, char **env)
{
	char *string = NULL, *argv[FUNCTION_H];
	int i, status;
	size_t n = 0;
	ssize_t num_char;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("Shell$ ");
		num_char = getline(&string, &n, stdin);
		if (num_char == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (string[i])
		{
			if (string[i] == '\n')
				string[i] = 0;
			i++;
		}
		tokenize_input(string, argv);
		if (strcmp(argv[0], "exit") == 0)
		{
			status = argv[1] ? atoi(argv[1]) : EXIT_SUCCESS;
			free(string);
			exit(status);
		}
		else if (strcmp(argv[0], "env") == 0)
			print_env(env);
		else if (access(argv[0], X_OK) == 0)
			execute_command(argv, env);
		else
			printf("%s: No such file or directory\n", av[0]);
	}
}

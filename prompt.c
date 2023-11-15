#include "Functions.h"
/**
 * read_and_parse_input - A void
 * @argv: A character
 * @env: Another character
 * Return: Always value
 */
void read_and_parse_input(char **argv, char **env)
{
	char *string = NULL;
	size_t n = 0;
	ssize_t num_char;
	int i,  j;

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
	j = 0;
	argv[j] = strtok(string, " ");
	if (argv[j] == NULL)
		return;
	while (argv[j])
		argv[++j] = strtok(NULL, " ");
	if (strcmp(argv[0], "exit") == 0)
	{
		free(string);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(argv[0], "env") == 0)
		handle_env(env);
	else if (strcmp(argv[0], "setenv") == 0)
		handle_setenv(argv);
	else if (strcmp(argv[0], "unsetenv") == 0)
		handle_unsetenv(argv);
}
/**
 * execute_command - A void
 * @argv: A character
 * @env: Another character
 */
void execute_command(char **argv, char **env)
{
	if (argv[0][0] == '/')
	{
		execute_absolute_path(argv, env);
	}
	else
	{
		execute_relative_path(argv, env);
	}
}
/**
 * prompt - A void
 * @env: A character
 */
void prompt(char **env)
{
	char *argv[FUNCTION_H];

	while (1)
	{
		read_and_parse_input(argv, env);
		execute_command(argv, env);
	}
}

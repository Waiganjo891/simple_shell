#include "Functions.h"
/**
 * prompt - A void
 * @env: Another character
 */
void prompt(char **env)
{
	char *string = NULL, *argv[FUNCTION_H];
	pid_t child_pid;
	int status;
	char filepath[1024], *path, *path_copy, *directory;
	int i, j, a;
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
		j = 0;
		argv[j] = strtok(string, " ");
		if (argv[j] == NULL)
			continue;
		while (argv[j])
			argv[++j] = strtok(NULL, " ");
		if (strcmp(argv[0], "exit") == 0)
		{
			free(string);
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			a = 0;

			while (env[a] != NULL)
			{
				printf("%s\n", env[a]);
				a++;
			}
		}
		else if (strcmp(argv[0], "setenv") == 0)
			handle_setenv(argv);
		else if (strcmp(argv[0], "unsetenv") == 0)
			handle_unsetenv(argv);
		else
		{
			if (argv[0][0] == '/')
			{
				if (access(argv[0], X_OK) == 0)
				{
					child_pid = fork();
					if (child_pid == -1)
					{
						free(string);
						exit(EXIT_FAILURE);
					}
					else if (child_pid == 0)
					{
						if (execve(argv[0], argv, env) == -1)
						{
							perror("execve");
							exit(EXIT_FAILURE);
						}
					}
					else
						wait(&status);
				}
				else
				{
					printf("%s: No such file or directory\n", argv[0]);
				}
			}
			else
			{
				{
				path = getenv("PATH");
				path_copy = strdup(path);
				directory = strtok(path_copy, ":");
				while (directory)
				{
					sprintf(filepath, "%s/%s", directory, argv[0]);
					if (access(filepath, X_OK) == 0)
					{
						child_pid = fork();
						if (child_pid == -1)
						{
							free(string);
							exit(EXIT_FAILURE);
						}
						else if (child_pid == 0)
						{
							if (execve(filepath, argv, env) == -1)
							{
								perror("execve");
								exit(EXIT_FAILURE);
							}
						}
						else
							wait(&status);
						break;
					}
					directory = strtok(NULL, ":");
				}
				free(path_copy);
			}
			if (!directory)
			{
				printf("%s: No such file or directory\n", argv[0]);
			}
			}
		}
	}
}

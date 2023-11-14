#include "Functions.h"
/**
 * main - An integer
 * @argc: Another integer
 * @argv: A character
 * @env: Another character
 * Return: Always (0)
 */
int main(int argc, char **argv, char **env)
{
	(void)argv;

	if (argc == 1)
		prompt(env);
	return (0);
}

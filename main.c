#include "Functions.h"
/**
 * main - An integer
 * @ac: Another integer
 * @argv: A character
 * @env: Another character
 * Return: Always (0)
 */
int main(int ac, char **argv, char **env)
{
	(void)argv;

	if (ac == 1)
		prompt(env);
	return (0);
}

#include "Functions.h"
/**
 * main - An integer
 * @ac: Another integer
 * @av: A character
 * @env: Another character
 * Return: Always (0)
 */
int main(int ac, char **av, char **env)
{
	if (ac == 1)
		prompt(av, env);
	return (0);
}

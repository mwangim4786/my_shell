#include "shell.h"

/**
 * main - main function
 * @ac: arguments count.
 * @av: arguments vector.
 * @env: environment variables vector.
 *
 * Return: Always 0.
 */

int main(int ac, char **av, char **env)
{
	if (ac == 1)
		prompt(av, env);

	return (0);
}


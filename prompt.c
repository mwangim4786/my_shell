#include "shell.h"

/**
 * prompt - function
 * @av: arguments vector pointer.
 * @env: env. variable pointer.
 */

void prompt(char **av, char **env)
{
	char *prompt = "cisfun$ ";

	
	
	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, prompt, 8);

	
}


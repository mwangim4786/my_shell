#include "shell.h"
//---
void prompt(char *string)
{
	//char *string = "xyz$ ";
	write(STDOUT_FILENO, string, 8);
}

//---------------------

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t lineSize = 0;

	lineSize = getline(&line, &len, stdin);

	return (line);

}



int main(int argc, char **argv, char **env)
{
	char *str = "xyz$ ";
	char *myLine = NULL;
	while(1)
	{
		if (isatty(STDIN_FILENO))
			prompt(str);

		myLine = read_line();
		write(STDOUT_FILENO, myLine, 8);
	}



	return (0);
}

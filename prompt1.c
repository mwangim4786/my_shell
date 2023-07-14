#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{

	char *buf = NULL, *prompt =  "xyz$ ";
	size_t bytes = 10;

	buf = malloc(sizeof(char) * bytes);

		while(1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, prompt, 13);

			getline(&buf, &bytes, stdin);

		}
	

	return 0;
}

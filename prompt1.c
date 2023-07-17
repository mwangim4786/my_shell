#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


char *get_location(char *argv_zero)
{
        char *path, *path_copy, *path_token, *file_path;
        int argv_zero_length, dir_len;
        struct stat buffer;

        path = getenv("PATH");

        if(path)
        {
                path_copy = strdup(path);
                argv_zero_length = strlen(argv_zero);

                path_token = strtok(path_copy, ":");

                while(path_token != NULL)
                {
                        dir_len = strlen(path_token);
                        file_path = malloc(argv_zero_length + dir_len + 2);
                        strcpy(file_path, path_token);
                        strcat(file_path, "/");
                        strcat(file_path, argv_zero);
                        strcat(file_path, "\0");

                        if(stat(file_path, &buffer) == 0)
                        {
                                free(path_copy);

                                return (file_path);
                        }
                        else
                        {
                                free(file_path);
                                 path_token = strtok(NULL, ":");
                        }
                }

                if (stat(argv_zero, &buffer) == 0)
                {
                        return (argv_zero);
                }

                return (NULL);
        }

        return (NULL);
}




void exec(char **argv)
{
	char *argv_zero = NULL, *command = NULL;

	if(argv)
	{
		argv_zero = argv[0];

		command = get_location(argv_zero);

		if(execve(command, argv, NULL) == -1)
                {
                        perror("There was an error!");
                }
	}


}


int main(int ac, char **argv)
{

	char *line = NULL, *prompt =  "xyz$ ";
	size_t bytes = 0;
	ssize_t no_of_chars;
	char *line_copy = NULL;
	const char *delim = " \n";
	int num_of_tokens = 0;
	char *token;
	int i, counter;


	/*line = malloc(sizeof(char) * bytes);*/

		while(1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, prompt, strlen(prompt));
				/*printf("%s", prompt);*/

			no_of_chars = getline(&line, &bytes, stdin);

			if (no_of_chars == -1)
			{
				printf("Exiting Shell \n");
				return (-1);
			}

			/*printf("%s\n", buf);*/
			/*write(STDOUT_FILENO, line, strlen(line));*/

			line_copy = malloc(sizeof(char) * no_of_chars);
			if (line_copy == NULL){
				perror("Error: Memory allocation error");
				return (-1);
			}

			strcpy(line_copy, line);

			token = strtok(line, delim);

			while (token != NULL){
				num_of_tokens++;
				token = strtok(NULL, delim);
			}
			num_of_tokens++;

			argv = malloc(sizeof(char *) * num_of_tokens);

			token = strtok(line_copy, delim);

			for (i = 0; token != NULL; i++){
				argv[i] = malloc(sizeof(char) * strlen(token));
				strcpy(argv[i], token);

				token = strtok(NULL, delim);
			}
			argv[i] = NULL;

			exec(argv);

			/*for (counter = 0; counter<num_of_tokens-1; counter++)
			{
				printf("%s\n", argv[counter]);
			}*/


		}
		
		free(line);
		free(line_copy);
		free(argv);

	return 0;
}

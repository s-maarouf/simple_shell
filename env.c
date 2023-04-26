#include "shell.h"

/**
  * main - Entry point to the Shell
  *
  * Return: Always zero.
  */
int main(void)
{
	char *line = NULL, **u_tokns = NULL;
	int w_len = 0, execFlag = 0;
	size_t line_size = 0;
	ssize_t line_len = 0;

	while (line_len >= 0)
	{
		signal(SIGINT, signal_handler);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		line_len = getline(&line, &line_size, stdin);
		if (line_len == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		w_len = count_input(line);
		if (line[0] != '\n' && w_len > 0)
		{
			u_tokns = tokenize(line, " \t", w_len);
			execFlag = execBuiltInCommands(u_tokns, line);
			if (!execFlag)
			{
				u_tokns[0] = find(u_tokns[0]);
				if (u_tokns[0] && access(u_tokns[0], X_OK) == 0)
					exec(u_tokns[0], u_tokns);
				else
					perror("./hsh");
			}

			frees_tokens(u_tokns);
		}
	}

	free(line);
	return (0);
}
int execBuiltInCommands(char **args, char *line)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		frees_tokens(args);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
			chdir(getenv("HOME"));
		else if (chdir(args[1]) == -1)
			perror(args[1]);
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (1);
		}
		if (setenv(args[1], args[2], 1) == -1)
		{
			perror("setenv");
			return (1);
		}
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1] == NULL || args[2] != NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}
		if (unsetenv(args[1]) == -1)
		{
			perror("unsetenv");
			return (1);
		}
	}
	else
		return (0);

	return (1);
}

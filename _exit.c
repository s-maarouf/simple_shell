#include "shell.h"

/**
 * _handle_exit - ...
 * @u_tokns: ...
 * @line: ...
 *
 * Return: Nothing
 */
void _handle_exit(char **u_tokns, char *line)
{
	int exit_status = 0;

	if (u_tokns[1] != NULL)
	{
		exit_status = atoi(u_tokns[1]);
		if (exit_status == 0 && strcmp(u_tokns[1], "0") != 0)
		{
			printf("exit: %s: numeric argument required\n", u_tokns[1]);
			return;
		}
	}

	free(line);
	frees_tokens(u_tokns);
	exit(exit_status);
}

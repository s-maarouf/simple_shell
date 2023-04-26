#include "shell.h"

/**
 * shell_setenv - Initialize a new environment variable, or modify an existing one
 * @vars: Array of environment variables
 * @name: Name of the environment variable to set
 * @value: Value to set the environment variable to
 *
 * Return: On success, 0. On failure, -1.
 */
int shell_setenv(char ***vars, const char *name, const char *value)

{
	char *new_var;
	size_t name_len = strlen(name);
	size_t value_len = strlen(value);

	new_var = malloc(name_len + value_len + 2);
	if (!new_var)
		return (-1);

	sprintf(new_var, "%s=%s", name, value);

	if (setenv(name, value, 1) < 0)
	{
		free(new_var);
		return (-1);
	}

	*vars = realloc(*vars, sizeof(char *) * ((*vars_len) + 2));
	if (!*vars)
	{
		free(new_var);
		return (-1);
	}

	(*vars)[*vars_len] = new_var;
	(*vars)[*vars_len + 1] = NULL;
	(*vars_len)++;

	return (0);
}

/**
 * shell_unsetenv - Remove an environment variable
 * @vars: Array of environment variables
 * @name: Name of the environment variable to remove
 *
 * Return: On success, 0. On failure, -1.
 */
int shell_unsetenv(char ***vars, const char *name)

{
	char **current_var;
	size_t name_len = strlen(name);

	current_var = *vars;
	while (*current_var)
	{
		if (strncmp(name, *current_var, name_len) == 0 && (*current_var)[name_len] == '=')
		{
			unsetenv(name);
			free(*current_var);
			while (*(current_var + 1))
			{
				*current_var = *(current_var + 1);
				current_var++;
			}
			*current_var = NULL;
			(*vars_len)--;
			*vars = realloc(*vars, sizeof(char *) * (*vars_len + 1))
				return (0);
		}
		current_var++;
	}

	return (-1);
}

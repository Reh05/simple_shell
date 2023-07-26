#include "shell.h"

/**
 * parse_command - determines the type of the command
 *
 * @command: command to be parsed
 *
 * Description:
 *      EXTERNAL_COMMAND (1) represents commands that start with a '/'
 *      INTERNAL_COMMAND (2) represents internal commands like "exit" or "env"
 *      PATH_COMMAND (3) represents comnds found in the PATH environment var
 *      INVALID_COMMAND (-1) represents invalid commands
 *
 * Return: constant representing the type of the command
 */
int parse_command(char *command)
{
	int b;
	char *internal_command[] = {"env", "exit", NULL};
	char *pth = NULL;

	for (b = 0; command[b] != '\0'; b++)
	{
		if (command[b] == '/')
		{
			return (EXTERNAL_COMMAND);
		}
	}
	for (b = 0; internal_command[b] != NULL; b++)
	{
		if (_strcmp(command, internal_command[b]) == 0)
		{
			return (INTERNAL_COMMAND);
		}
	}
	pth = check_path(command);
	if (pth != NULL)
	{
		free(pth);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}
/**
 * execute_command - function executes a command
 *
 * @tokenized_command: tokenized form of the command (ls -l == {ls, -l, NULL})
 *
 * @command_type: the command type
 *
 * Return: void
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execve(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_func(tokenized_command[0]);
		func(tokenized_command);
	}
	if (command_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - this part checks if a command is found in the PATH
 *
 * @command: command used
 *
 * Return: path of the command found, else, return NULL if not found
 */
char *check_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int b;

	if (path == NULL || _strlen(path) == 0)
	{
		return (NULL);
	}
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (b = 0; path_array[b] != NULL; b++)
	{
		temp2 = _strcat(path_array[b], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - this retrieves a function based on the command given & a map
 *
 * @command: string to check
 *
 * Return: void
 */
void (*get_func(char *command))(char **)
{
	int b;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (b = 0; b < 2; b++)
	{
		if (_strcmp(command, mapping[b].command_name) == 0)
		{
			return (mapping[b].func);
		}
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_copy;

	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_copy = name;
		     *pair_ptr == *name_copy; pair_ptr++, name_copy++)
		{
			if (*pair_ptr == '=')
			{
				break;
			}
		}
		if ((*pair_ptr == '=') && (*name_copy == '\0'))
		{
			return (pair_ptr + 1);
		}
	}
	return (NULL);
}

#include "shell.h"

/**
 * initializer - the function executes the files
 *
 * @current_command: checking current token
 *
 * @type_command: split token
 *
 * Return: void
 */
void initializer(char **current_command, int type_command)
{
	pid_t pid;

	if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			execute_command(current_command, type_command);
		}
		else
		{
			waitpid(pid, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(current_command, type_command);
}

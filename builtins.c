#include "shell.h"

/**
 * env - Prints the current environment.
 *
 * @tokenized_command: Command entered (unused).
 *
 * This function prints the current environment variables.
 * It iterates over the `environ` array and prints each variable
 * followed by a newline.
 *
 * Return: void
 */
void env(char **tokenized_command __attribute__((unused)))
{
	int b;

	for (b = 0; environ[b] != NULL; b++)
	{
		print(environ[b], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - Exits the shell.
 *
 * @tokenized_command: Command entered.
 *
 * This function handles the "quit" command to exit the shell.
 * If no argument is provided, it simply exits the shell.
 * If an argument is provided, it attempts to convert it to an integer.
 * If the conversion is successful, it exits the shell with the
 *	specified exit code.
 * If the argument is not a valid number, it prints an error message
 *	and sets the status to 2.
 * If more than one argument is provided, it prints an error message.
 *
 * Return: void
 */
void quit(char **tokenized_command)
{
	int num_token = 0, arg;

	for (; tokenized_command[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free(tokenized_command);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_token == 2)
	{
		arg = _atoi(tokenized_command[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tokenized_command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tokenized_command);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n",
				STDERR_FILENO);
}

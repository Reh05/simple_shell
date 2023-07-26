#include "shell.h"

void non_interactive(void);
void initializer(char **current_command, int type_command);

/**
 * main - shell code
 *
 * @argc: number of arguments passed
 *
 * @argv: program arguments
 *
 * Description:
 *    - Applies the functions in utils and helpers
 *    - Implements EOF
 *    - Prints error on failure
 *
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	char **current_command = NULL, *shell_name = NULL;
	char **commands = NULL, *line = NULL;
	int b, type_command = 0, status = 0;
	size_t n = 0;

	(void)argc;

	signal(SIGINT, ctrl_c_handler);
	shell_name = argv[0];
	while (1)
	{
		non_interactive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
			remove_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");

		for (b = 0; commands[b] != NULL; b++)
		{
			current_command = tokenizer(commands[b], " ");
			if (current_command[0] == NULL)
			{
				free(current_command);
				break;
			}
			type_command = parse_command(current_command[0]);

			initializer(current_command, type_command);
			free(current_command);
		}
		free(commands);
	}
	free(line);

	return (status);
}
/**
 * non_interactive - function that handles shell non-interactive mode
 *
 * Description:
 *    - Reads input from stdin until EOF (End Of File)
 *    - Tokenizes input and processes commands
 *    - Exits with the current shell status
 *
 * Return: void return type
 */
void non_interactive(void)
{
	char **current_command = NULL;
	int b, type_command = 0;
	size_t num = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &num, stdin) != -1)
		{
			remove_newline(line);
			remove_comment(line);
			commands = tokenizer(line, ";");
			for (b = 0; commands[b] != NULL; b++)
			{
				current_command = tokenizer(commands[b], " ");
				if (current_command[0] == NULL)
				{
					free(current_command);
					break;
				}
				type_command = parse_command(current_command[0]);
				initializer(current_command, type_command);
				free(current_command);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
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

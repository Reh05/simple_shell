#include "shell.h"

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

char *shell_name = NULL;
char **commands = NULL;
char *line = NULL;
int status = 0;

int main(int argc, char **argv)
{
	char **current_command = NULL;
	int b, type_command = 0;
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

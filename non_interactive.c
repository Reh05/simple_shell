#include "shell.h"

/**
 * non_interactive - function that handles shell non-interactive mode
 *
 * Description:
 *    - Reads input from stdin until EOF
 *    - Tokenizes input and processes commands
 *    - Exits with the current shell status
 *
 * Return: void
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

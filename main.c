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
		if (custom_getline(&line, &n, stdin) == -1)
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
 * assign_line_ptr - Reassigns the lineptr variable for _getline.
 *
 * @line_ptr: buffer to store an input string.
 *
 * @n: size of lineptr.
 *
 * @buff: string to assign to line_ptr.
 *
 * @b: size of buffer.
 *
 * Return: void return type
 */
void assign_line_ptr(char **line_ptr, size_t *n, char *buff, size_t b)
{
	if (*line_ptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*line_ptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*line_ptr = buff;
	}
	else
	{
		_strcpy(*line_ptr, buff);
		free(buff);
	}
}

/**
 * custom_getline - Mimics the built-in getline function.
 *
 * @line_ptr: buffer to store the input.
 *
 * @n: size of lineptr.
 *
 * @stream: stream to read from.
 *
 * Return: number of bytes read.
 */
ssize_t custom_getline(char **line_ptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buff;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
			free(buff);
			return (-1);
		if (r == 0 && input != 0)
			input++;
			break;
		if (input >= 120)
			buff = _realloc(buff, input, input + 1);

		buff[input] = c;
		input++;
	}
	buff[input] = '\0';

	assign_line_ptr(line_ptr, n, buff, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}

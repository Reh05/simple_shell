#include "shell.h"

/**
 * tokenizer - Tokenizes the input string and stores it into an array.
 *
 * @input_string: Input string to be parsed.
 *
 * @delim: Delimiter to be used (must be a single character string).
 *
 * This function tokenizes the input string using the specified delimiter
 * and stores the tokens in an array. It dynamically reallocates memory as
 * needed to accommodate the tokens. The last element of the
 * array is set to NULL.
 *
 * Return: Array of tokens.
 */
char **tokenizer(char *input_string, char *delim)
{
	int num_tokens = 0;
	char **tokens = NULL;
	char *token = NULL;
	char *save_ptr = NULL;

	token = _strtok_r(input_string, delim, &save_ptr);

	while (token != NULL)
	{
		tokens = _realloc(tokens, sizeof(*tokens) * num_tokens,
				sizeof(*tokens) * (num_tokens + 1));
		tokens[num_tokens] = token;
		token = _strtok_r(NULL, delim, &save_ptr);
		num_tokens++;
	}

	tokens = _realloc(tokens, sizeof(*tokens) * num_tokens,
			sizeof(*tokens) * (num_tokens + 1));
	tokens[num_tokens] = NULL;

	return (tokens);
}

/**
 * print - Prints a string to the specified stream.
 *
 * @string: String to be printed.
 *
 * @stream: Stream to print out to.
 *
 * This function writes each character of the string to the specified stream.
 *
 * Return: void
 */
void print(char *string, int stream)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
	{
		write(stream, &string[i], 1);
	}
}

/**
 * remove_newline - Removes the newline character from a string.
 *
 * @str: String to be modified.
 *
 * This function replaces the newline character ('\n') in the string with
 * a null terminator ('\0'), effectively removing the newline.
 *
 * Return: void
 */
void remove_newline(char *str)
{
	int b = 0;

	while (str[b] != '\0')
	{
		if (str[b] == '\n')
		{
			break;
		}
		b++;
	}
	str[b] = '\0';
}

/**
 * _strcpy - Copies a string from source to destination.
 *
 * @source: Source string to copy from.
 *
 * @dest: Destination string to copy to.
 *
 * This function copies the contents of the source string to the
 * destination string.
 * The destination string must have enough space to hold the source string.
 *
 * Return: void
 */
void _strcpy(char *source, char *dest)
{
	int b = 0;

	for (; source[b] != '\0'; b++)
	{
		dest[b] = source[b];
	}
	dest[b] = '\0';
}

/**
 * _strlen - Calculates the length of a string.
 *
 * @string: String to be measured.
 *
 * This function counts the number of characters in the string
 * until the null terminator is encountered.
 *
 * Return: Length of the string.
 */
int _strlen(char *string)
{
	int leng = 0;

	if (string == NULL)
	{
		return (leng);
	}
	for (; string[leng] != '\0'; leng++)
	{
		;
	}
	return (leng);
}

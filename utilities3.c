#include "shell.h"

/**
 *_strtok_r - function that tokenizes a string
 *
 *@string: string
 *
 *@delim: delimiter
 *
 *@save_ptr: pointer
 *
 *Return: next available token
 */
char *_strtok_r(char *string, char *delim, char **save_ptr)
{
	char *fin;

	if (string == NULL)
	{
		string = *save_ptr;
	}
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	string = string + _strspn(string, delim);
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	fin = string + _strcspn(string, delim);
	if (*fin == '\0')
	{
		*save_ptr = fin;
		return (string);
	}

	*fin = '\0';
	*save_ptr = fin + 1;
	return (string);
}

/**
 * _atoi - function that changes a string to an integer
 *
 * @s: string to be changed
 *
 * Return: converted integer
 */
int _atoi(char *s)
{
	unsigned int num = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			num = (num * 10) + (*s - '0');
		else if (num > 0)
			break;
	} while (*s++);
	return (num);
}

/**
 * _realloc - function that reallocates a memory block
 *
 * @ptr: pointer
 *
 * @old_size: size
 *
 * @new_size: size
 *
 * Return: pointer to the address of the new memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *block;
	unsigned int i;

	if (ptr == NULL)
	{
		block = malloc(new_size);
		return (block);
	}
	else if (new_size == old_size)
	{
		return (ptr);
	}
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		block = malloc(new_size);
		if (block != NULL)
		{
			for (i = 0; i < min(old_size, new_size); i++)
			{
				*((char *)block + i) = *((char *)ptr + i);
			}
			free(ptr);
			return (block);
		}
		else
		{
			return (NULL);
		}

	}
}

/**
 * ctrl_c_handler - function that handles the CTRL-C signal
 *
 * @signum: signal
 *
 * Return: void
 */
void ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		print("\n($) ", STDIN_FILENO);
	}
}

/**
 * remove_comment - function that removes/ignores everything after a '#' char
 *
 * @input: input used
 *
 * Return: void
 */
void remove_comment(char *input)
{
	int b = 0;

	if (input[b] == '#')
		input[b] = '\0';
	while (input[b] != '\0')
	{
		if (input[b] == '#' && input[b - 1] == ' ')
		{
			break;
		}
		b++;
	}
	input[b] = '\0';
}

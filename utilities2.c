#include "shell.h"

/**
 *_strcmp - function that compares two strings
 *
 *@first: first string
 *
 *@second: second string
 *
 * Return: the very difference of the two strings
 */

int _strcmp(char *first, char *second)
{
	int b = 0;

	while (first[b] != '\0')
	{
		if (first[b] != second[b])
		{
			break;
		}
		b++;
	}
	return (first[b] - second[b]);
}

/**
 *_strcat - function that concatenates two strings
 *
 *@destination: string
 *
 *@source:  string
 *
 * Return: address of the new string
 */

char *_strcat(char *destination, char *source)
{
	char *new =  NULL;
	int leng_dest = _strlen(destination);
	int leng_source = _strlen(source);

	new = malloc(sizeof(*new) * (leng_dest + leng_source + 1));
	_strcpy(destination, new);
	_strcpy(source, new + leng_dest);
	new[leng_dest + leng_source] = '\0';
	return (new);
}

/**
 *_strspn - function that gets the length of a prefix substring
 *
 *@str1: string to be searched
 *
 *@str2: string to be used
 *
 *Return: number of bytes in the initial segment
 */

int _strspn(char *str1, char *str2)
{
	int b = 0;
	int match = 0;

	while (str1[b] != '\0')
	{
		if (_strchr(str2, str1[b]) == NULL)
		{
			break;
		}
		match++;
		b++;
	}
	return (match);
}

/**
 *_strcspn - computes segment of str1 which consists of characters not in str2
 *@str1: string to be searched
 *@str2: string to be used
 *
 *Return: index at which a char in str1 exists in str2
 */

int _strcspn(char *str1, char *str2)
{
	int leng = 0, i;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (_strchr(str2, str1[i]) != NULL)
		{
			break;
		}
		leng++;
	}
	return (leng);
}

/**
 *_strchr - function that locates a char in a string
 *
 *@s: string to be searched
 *
 *@c: char to be checked
 *
 *Return: pointer to the first occurence of c in s
 */

char *_strchr(char *s, char c)
{
	int b = 0;

	for (; s[b] != c && s[b] != '\0'; b++)
	{
		;
	}
	if (s[b] == c)
	{
		return (s + b);
	}
	else
	{
		return (NULL);
	}
}

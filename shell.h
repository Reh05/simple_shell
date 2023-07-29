#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/* Constants */
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * struct map - struct that maps a command name to a function
 *
 * @command_name: name of the command
 *
 * @func: function that executes the command
 */
typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

/* Main Functions */
void non_interactive(void);
void initializer(char **current_command, int type_command);

/* Utility Functions */
int parse_command(char *command);
void execute_command(char **args, int type);
char *check_path(char *command);
void (*get_func(char *command))(char **);
char *_getenv(char *name);

/* External Variables */
extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/* Helper Functions */
void print(char *message, int newline);
char **tokenizer(char *input, char *delimiter);
void remove_newline(char *str);
int _strlen(char *str);
void _strcpy(char *dest, char *src);

/* String Manipulation Functions */
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, char *src);
int _strspn(char *str, char *delimiters);
int _strcspn(char *str, char *delimiters);
char *_strchr(char *str, char character);

/* Additional Helper Functions */
char *_strtok_r(char *str, char *delimiters, char **saveptr);
int _atoi(char *str);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int signum);
void remove_comment(char *str);

/* Built-in Commands */
void env(char **args);
void quit(char **args);

/* Getline Function Prototypes */
void assign_line_ptr(char **line_ptr, size_t *n, char *buff, size_t b);
ssize_t custom_getline(char **line_ptr, size_t *n, FILE *stream);

#endif /* SHELL_H */

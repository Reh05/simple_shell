#ifndef SHELL_H
#define SHELL_H

/* Function Prototypes */
void ctrl_c_handler(int signal);
char **tokenizer(char *str, char *delimiters);
void free_tokens(char **tokens);

#endif /* SHELL_H */


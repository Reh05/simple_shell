#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"

#define MAX_COMMAND_LEN 1000

int main(void) {
    char command[MAX_COMMAND_LEN];

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) > 0) {

            char **tokens = tokenizer(command, " ");
            if (tokens[0] == NULL) {
                free_tokens(tokens);
                continue;
            }

            pid_t pid = fork();
            if (pid == -1) {
                perror("fork error");
                free_tokens(tokens);
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                execve(tokens[0], tokens, NULL);
                fprintf(stderr, "%s: command not found\n", tokens[0]);
                free_tokens(tokens);
                exit(EXIT_FAILURE);
            } else {
                int status;
                waitpid(pid, &status, 0);
                free_tokens(tokens);
            }
        }
    }

    return 0;
}

/* Signal handler for Ctrl+C */
void ctrl_c_handler(int signal) {
    (void)signal;
    printf("\n#cisfun$ ");
    fflush(stdout);
}

/* Tokenize a string based on delimiters */
char **tokenizer(char *str, char *delimiters) {
    char **tokens = NULL;
    char *token;
    int i = 0;

    tokens = malloc(sizeof(char *));
    if (tokens == NULL) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    token = strtok(str, delimiters);
    while (token != NULL) {
        tokens[i] = token;
        i++;
        tokens = realloc(tokens, (i + 1) * sizeof(char *));
        if (tokens == NULL) {
            perror("realloc error");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, delimiters);
    }

    tokens[i] = NULL;
    return tokens;
}

/* Free the memory allocated for tokens */
void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

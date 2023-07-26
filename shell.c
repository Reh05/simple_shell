#include "shell.h"

int main() {
	char command[1000];

	while (1) {
		printf("$ ");
		fflush(stdout);

		if (fgets(command, sizeof(command), stdin) == NULL)
			break;

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';

		if (strlen(command) > 0) {
			if (access(command, X_OK) == 0) {
				pid_t pid = fork();

				if (pid == -1) {
					perror("fork error");
					exit(EXIT_FAILURE);
				} else if (pid == 0) {
					char *argv[2];
					argv[0] = command;
					argv[1] = NULL;

					if (execve(command, argv, environ) == -1) {
						fprintf(stderr, "%s: 1: %s: not found\n",
								command, command);
						exit(EXIT_FAILURE);
					}
				} else {
					int status;
					waitpid(pid, &status, 0);
				}
			} else {
				fprintf(stderr, "%s: 1: %s: not found\n", command, command);
			}
		}
		if (feof(stdin)) {
			printf("\n");
			break;
		}
	}

	return 0;
}

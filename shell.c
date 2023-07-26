#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LEN 1000

int main() {
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

            int result = system(command);

            if (result == -1) {
                fprintf(stderr, "%s: command not found\n", command);
            }
        }
    }

    return 0;
}


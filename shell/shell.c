#include "header.h"

// Function Prototypes
int dump(char* argv[]);

int main(void) {
    char* line = NULL;
    char* argv[64];
    size_t len = 0;


    while (1) {
        // Prompt the user for input
        printf("GabbaGuul> ");

        // Clear the output stored in the internal buffer
        fflush(stdout);
        
        // -1 here is equivalent to the user pressing "Ctrl + D"
        if (getline(&line, &len, stdin) == -1) {
            printf("\n");
            break;
        }

        // strip trailing newline
        line[strcspn(line, "\n")] = '\0';

        // Tokenise into argv[]
        int argc = 0;
        char* token = strtok(line, " \t\r\n");
        while (token != NULL && argc < 63) {
            argv[argc++] = token;
            // strtok remembers its internal state
            token = strtok(NULL, " \t\r\n");
        }
        // argv needs to be NULL terminated
        argv[argc] = NULL;

        // Skip empty line
        if (argc == 0) {
            continue;
        }

        // Builtins
        if (strcmp(argv[0], "exit") == 0) {
            printf("\n");
            break;
        } else if (strcmp(argv[0], "dump") == 0) {
            dump(argv);
            continue;
        }
        
    }

    free(line);
    return 0;
}

int dump(char* argv[]) {
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        // Child Process
        execvp(
            "./dump",
            argv
        );
        exit(1);
    } else {
        // Parent Process
        waitpid(pid, NULL, 0);
    }

    return 0;
}
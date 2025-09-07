#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"

int main(void) {
    char* line = NULL;
    char* argv[64];
    size_t len = 0;
    char buf[1024];


    // Word Art
    greet();

    while (1) {
        getcwd(buf, 1024);

        // Prompt the user for input
        printf("GabbaGuul:%s> ", buf);

        // Clear the output stored in the internal buffer
        fflush(stdout);
        
        // -1 here is equivalent to the user pressing "Ctrl + D"
        if (getline(&line, &len, stdin) == -1) {
            printf("\n");
            break;
        }

        // Strip trailing newline
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
        } else if (strcmp(argv[0], "pwd") == 0) {
            cmd_pwd();
            continue;
        } else if (strcmp(argv[0], "cd") == 0) {
            cmd_cd(argv);
            continue;
        } else if (strcmp(argv[0], "ls") == 0) {
            cmd_ls(argv);
            continue;
        } else if (strcmp(argv[0], "echo") == 0) {
            cmd_echo(argv);
            continue;
        } else if (strcmp(argv[0], "python") == 0) {
            cmd_python_mini();
            continue;
        } else {
            fprintf(stderr, "Unknown Command: %s\n", argv[0]);
        }
    }

    free(line);
    return 0;
}
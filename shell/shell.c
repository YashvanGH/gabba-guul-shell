#include "header.h"

// Function Prototypes
int dump(char* argv[]);
int greet(void);
int pwd(void);
int cd(char* argv[]);

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
        } else if (strcmp(argv[0], "pwd") == 0) {
            pwd();
            continue;
        } else if (strcmp(argv[0], "cd") == 0) {
            cd(argv);
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

int pwd(void) {
    char buf[1024];

    getcwd(buf, 1024);
    printf("Directory: %s\n", buf);
    return 0;
}

int cd(char* argv[]) {
    chdir(argv[1]);
    return 0;
}

int greet(void) {
    puts("   ____       _     _             ____              _ ");
    puts("  / ___| __ _| |__ | |__  __ _   / ___|_   _ _   _ | |");
    puts(" | |  _ / _` | '_ \\| '_ \\/ _` | | |  _| | | | | | || |");
    puts(" | |_| | (_| | |_) | |_)  (_| | | |_| | |_| | |_| || |");
    puts("  \\____|\\__,_|_.__/|_.__/\\__,_|  \\____|\\__,_|\\__,_||_|");
    puts("");
    return 0;
}
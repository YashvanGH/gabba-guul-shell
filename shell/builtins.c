#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// To not redefine the function prototypes
#include "shell.h"

int greet(void) {
    puts("   ____       _     _             ____              _ ");
    puts("  / ___| __ _| |__ | |__  __ _   / ___|_   _ _   _ | |");
    puts(" | |  _ / _` | '_ \\| '_ \\/ _` | | |  _| | | | | | || |");
    puts(" | |_| | (_| | |_) | |_)  (_| | | |_| | |_| | |_| || |");
    puts("  \\____|\\__,_|_.__/|_.__/\\__,_|  \\____|\\__,_|\\__,_||_|");
    puts("");
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
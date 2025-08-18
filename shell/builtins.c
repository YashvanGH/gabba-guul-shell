#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
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

    if (pid == -1) {
        perror("fork");
        return 0;
    }

    if (pid == 0) {
        // Child Process
        execvp(argv[0], argv);
        perror("execvp ./dump");
        exit(127); // Error code for command not found
    } else {
        // Parent Process
        waitpid(pid, NULL, 0);
    }

    return 1;
}

int pwd(void) {
    char buf[1024];

    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd");
        return 0;
    }

    printf("Directory: %s\n", buf);
    return 1;
}

int cd(char* argv[]) {

    if (!argv[1]) {
        fprintf(stderr, "cd: Missing argument\n");
        return 1;
    }

    if (chdir(argv[1]) == -1) {
        fprintf(stderr, "cd: %s: %s\n", argv[1], strerror(errno));
        return 1;
    }

    return 0;
}

int ls(char* argv[]) {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 0;
    }

    if (pid == 0) {
        // Child Process
        execvp(argv[0], argv);
        fprintf(stderr, "ls: %s\n", strerror(errno));
        exit(127);
    } else {
        waitpid(pid, NULL, 0);
    }

    return 1;
}

// git bin exec
// echo > >>
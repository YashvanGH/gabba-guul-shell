#define _POSIX_C_SOURCE 200809L // Tells the compiler you want to use the POSIX 2008 standard
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// To not redefine the function prototypes
#include "shell.h"

/* Helpers */
static int wait_for_child(pid_t pid) {
    int status;
    
    for (;;) {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno == EINTR) {
                // Retry execution if it was interrupted by a signal
                continue;
            } else {
                perror("waitpid");
                return 127;
            }
        }
        break;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status)) {
        return 128 + WTERMSIG(status); // Common convention to get the exit status/code
    }

    return 127; // Exit with error
}

static int run_external(char* argv[]) {
    if (!argv || !argv[0]) {
        fprintf(stderr, "exec: empty argv\n");
        return 127;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 127;
    }

    if (pid == 0) {
        /* --- Child Process --- */

        // Restore default SIGINT so ctrl + c kills the child and not the parent/shell
        struct sigaction sa = {0}; // Shorthand for initally to "empty" values in sigaction struct
        sa.sa_handler = SIG_DFL;
        // Modifying the interrupt signal to its default behaviour in the child process
        sigaction(SIGINT, &sa, NULL);

        execvp(argv[0], argv);
        // On error
        int err = errno;
        fprintf(stderr, "%s: %s\n", argv[0], strerror(err));
        exit(err == ENOENT ? 127 : 126);
    }

    /* --- Parent Process --- */
    return wait_for_child(pid);
}

/* Builtins*/
int greet(void) {
    puts("   ____       _     _             ____              _ ");
    puts("  / ___| __ _| |__ | |__  __ _   / ___|_   _ _   _ | |");
    puts(" | |  _ / _` | '_ \\| '_ \\/ _` | | |  _| | | | | | || |");
    puts(" | |_| | (_| | |_) | |_)  (_| | | |_| | |_| | |_| || |");
    puts("  \\____|\\__,_|_.__/|_.__/\\__,_|  \\____|\\__,_|\\__,_||_|");
    puts("");
    return 0;
}

int cmd_pwd(void) {
    char buf[1024];

    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("Directory: %s\n", buf);
    return 0;
}

int cmd_cd(char* argv[]) {
    const char* dir = argv[1];

    if (!dir) {
        fprintf(stderr, "cd: Missing argument\n");
        return 1;
    }

    if (chdir(dir) == -1) {
        fprintf(stderr, "cd: %s: %s\n", dir, strerror(errno));
        return 1;
    }

    return 0;
}

int cmd_ls(char* argv[]) {
    return run_external(argv);
}

int cmd_echo(char* argv[]) {
    return run_external(argv);
}

int cmd_python_mini() {
    pid_t pid;
    char *argv[] = { "python.exe", NULL };

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 0;
    }

    if (pid == 0) {
        // Child Process
        execvp("python.exe", argv);
        fprintf(stderr, "python shell: %s\n", strerror(errno));
        exit(1);
    } else {
        // Parent Process
        waitpid(pid, NULL, 0);
    }

    return 0;
}
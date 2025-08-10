#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main() {
    // Array of strings
    char* args[] = {
        "args", // argv[0]: program name
        "arg1",
        "arg2",
        "arg3",
        NULL
    };

    execvp(
        "args_code/args",
        args
    );

    printf("Failed.\n");
    return 0;
}

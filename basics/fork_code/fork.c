#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // Process ID type
    pid_t pid;
    // Used for exit status of child and wait status of parent
    int rv;

    // After calling fork(), there are now 2 process, child and parent
    // fork() returns -1 -> fork failed, 0 -> in the new child process, >0 -> child's PID in the parent process
    pid = fork();

    switch (pid) {
    case -1: // fork failed
        perror("fork");
        exit(1);

    case 0: // child process
        printf("CHILD: This is the child process!\n");
        printf("CHILD: My PID is %d\n", getpid()); // Gets their own PID
        printf("CHILD: My parent's PID is %d\n", getppid()); // Gets the parents PID
        printf("CHILD: Enter my exit status (make it small): ");
        scanf(" %d", &rv);
        printf("CHILD: I'm outta here!\n");
        exit(rv);

    default: // parent process
        printf("PARENT: This is the parent process!\n");
        printf("PARENT: My PID is %d\n", getpid()); // Gets their own PID
        printf("PARENT: My child's PID is %d\n", pid); // This is the child PID as fork() returned >0
        printf("PARENT: I'm now waiting for my child to exit()...\n");

        wait(&rv);
        printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv)); // Extracts the numeric exit code the child passed to exit(rv)
        printf("PARENT: I'm outta here!\n");
    }

    return 0;
}

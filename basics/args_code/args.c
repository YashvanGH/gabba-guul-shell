#include <stdio.h>

// argc -> argument counter which tells how many elements are in argv
// argv -> array of strings where 1st element is always the path to the executable
int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
}
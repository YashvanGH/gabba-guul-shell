#ifndef SHELL_HEADER // #ifndef -> if not defined
#define SHELL_HEADER // define this macro

int greet(void);
int dump(char* argv[]);
int pwd(void);
int cd(char* argv[]);
int ls(char* argv[]);

#endif // end definition
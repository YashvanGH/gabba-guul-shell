#ifndef SHELL_HEADER // #ifndef -> if not defined
#define SHELL_HEADER // define this macro

int greet(void);
int pwd(void);
int cd(char* argv[]);
int ls(char* argv[]);
int echo(char* argv[]);
int python_mini();

#endif // end definition
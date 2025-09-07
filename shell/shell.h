#ifndef SHELL_HEADER // #ifndef -> if not defined
#define SHELL_HEADER // define this macro

int greet(void);
int cmd_pwd(void);
int cmd_cd(char* argv[]);
int cmd_ls(char* argv[]);
int cmd_echo(char* argv[]);
int cmd_python_mini();

#endif // end definition
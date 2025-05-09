#ifndef BUILTINS_H
#define BUILTINS_H
#define True 1
#define False 0

extern char *get_prompt();
extern void custom_ls(int argc, char *args[]);
extern void custom_cat(int argc, char *args[]);
extern void custom_cd(int argc, char *args[]);
extern void custom_echo(int argc, char *args[]);
extern char *custom_pwd();
extern void custom_clear();
extern char *custom_whoami();

#endif

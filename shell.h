#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

int cmd_cd(char** args);
int cmd_help(char** args);
int cmd_exit(char** args);
int cmd_ls(char** args);
int cmd_pwd(char** args);
int cmd_clear(char** args);
int cmd_mkdir(char** args);
int cmd_rmdir(char** args);
int cmd_cat(char** args);
int cmd_touch(char** args);
int cmd_rm(char** args);

extern char* builtin_str[];
extern int (*builtin_func[]) (char**);

int num_builtins(void);
int launch_program(char** args);
int execute_command(char** args);
char* read_line(void);
char** split_line(char* line);
void shell_loop(void);

#endif
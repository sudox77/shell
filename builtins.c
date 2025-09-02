#include "shell.h"

char* builtin_str[] = {
    "cd",
    "help",
    "exit",
    "ls",
    "pwd",
    "clear"
};

int (*builtin_func[]) (char**) = {
    &cmd_cd,
    &cmd_help,
    &cmd_exit,
    &cmd_ls,
    &cmd_pwd,
    &cmd_clear
};

int num_builtins(void) {
    return sizeof(builtin_str) / sizeof(char*);
}

int cmd_cd(char** args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int cmd_help(char** args)
{
    int i;
    printf("Simple Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int cmd_exit(char** args)
{
    return 0;
}

int cmd_ls(char** args)
{
    DIR* dir;
    struct dirent* entry;
    struct stat file_stat;
    char* path = ".";

    if (args[1] != NULL) {
        path = args[1];
    }

    dir = opendir(path);
    if (dir == NULL) {
        perror("shell");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("%s  ", entry->d_name);
        }
    }
    printf("\n");

    closedir(dir);
    return 1;
}

int cmd_pwd(char** args)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    }
    else {
        perror("shell");
    }
    return 1;
}

int cmd_clear(char** args)
{
    printf("\033[2J\033[H");
    return 1;
}
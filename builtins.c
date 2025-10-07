#include "shell.h"

char* builtin_str[] = {
    "cd",
    "help",
    "exit",
    "ls",
    "pwd",
    "clear",
    "mkdir",
    "rmdir",
    "cat",
    "touch",
    "rm",
    "echo",
    "cp",
    "mv",
    "chmod"
};

int (*builtin_func[]) (char**) = {
    &cmd_cd,
    &cmd_help,
    &cmd_exit,
    &cmd_ls,
    &cmd_pwd,
    &cmd_clear,
    &cmd_mkdir,
    &cmd_rmdir,
    &cmd_cat,
    &cmd_touch,
    &cmd_rm,
    &cmd_echo,
    &cmd_cp,
    &cmd_mv,
    &cmd_chmod
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

int cmd_mkdir(char** args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"mkdir\"\n");
    }
    else {
        if (mkdir(args[1], 0755) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int cmd_rmdir(char** args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"rmdir\"\n");
    }
    else {
        if (rmdir(args[1]) != 0) {
            perror("shell");
        }
    }
    return 1;
}

int cmd_cat(char** args)
{
    FILE* file;
    char buffer[256];

    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"cat\"\n");
        return 1;
    }

    file = fopen(args[1], "r");
    if (file == NULL) {
        perror("shell");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return 1;
}

int cmd_touch(char** args)
{
    FILE* file;

    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"touch\"\n");
        return 1;
    }

    file = fopen(args[1], "a");
    if (file == NULL) {
        perror("shell");
        return 1;
    }

    fclose(file);
    return 1;
}

int cmd_rm(char** args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"rm\"\n");
        return 1;
    }

    if (unlink(args[1]) != 0) {
        perror("shell");
        return 1;
    }

    return 1;
}

int cmd_clear(char** args)
{
    printf("\033[2J\033[H");
    return 1;
}

int cmd_echo(char** args)
{
    if (args[1] == NULL) {
        printf("\n");
        return 1;
    }

    for (int i = 1; args[i] != NULL; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%s", args[i]);
    }
    printf("\n");
    return 1;
}

int cmd_cp(char** args)
{
    FILE* source;
    FILE* dest;
    char buffer[1024];
    size_t bytes;

    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "shell: expected two arguments to \"cp\"\n");
        return 1;
    }

    source = fopen(args[1], "rb");
    if (source == NULL) {
        perror("shell");
        return 1;
    }

    dest = fopen(args[2], "wb");
    if (dest == NULL) {
        perror("shell");
        fclose(source);
        return 1;
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(source);
    fclose(dest);
    return 1;
}

int cmd_mv(char** args)
{
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "shell: expected two arguments to \"mv\"\n");
        return 1;
    }

    if (rename(args[1], args[2]) != 0) {
        perror("shell");
        return 1;
    }

    return 1;
}

int cmd_chmod(char** args)
{
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "shell: expected two arguments to \"chmod\"\n");
        return 1;
    }

    // Convert octal string to integer
    int mode = strtol(args[1], NULL, 8);
    
    if (chmod(args[2], mode) != 0) {
        perror("shell");
        return 1;
    }

    return 1;
}
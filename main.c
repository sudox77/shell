#include "shell.h"

int launch_program(char** args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("shell");
    }
    else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int execute_command(char** args)
{
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch_program(args);
}

int main(int argc, char** argv)
{
    shell_loop();
    return EXIT_SUCCESS;
}
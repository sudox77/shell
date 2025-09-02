#include "shell.h"

char* read_line(void)
{
    int bufsize = RL_BUFSIZE;
    int position = 0;
    char* buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char** split_line(char* line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if (!tokens) {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void shell_loop(void)
{
    char* line;
    char** args;
    int status;

    do {
        printf("> ");
        line = read_line();
        args = split_line(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}
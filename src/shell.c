// shell.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <sys/types.h>
#include "../include/shell.h"
#include "../include/utils.h"

#define PROMPT_SYMBOL "grish(a)> "

void init_shell() {
    printf("\033[1;32mInitializing grish(a)...\033[0m\n");
}

void display_prompt() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char *user = getpwuid(getuid())->pw_name;

    printf("\033[1;34m%s\033[0m@\033[1;36mgrish(a)\033[0m:\033[1;33m%s\033[0m$ ", user, cwd);
    fflush(stdout);
}

char *read_input() {
    char *line = NULL;
    size_t len = 0;

    ssize_t read = getline(&line, &len, stdin);

    if (read == -1) {
        free(line);
        return NULL;  // Handle EOF or Ctrl+D
    }

    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    return line;
}

void cleanup_shell() {
}


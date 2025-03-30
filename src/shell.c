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

/**
 * Initializes shell state, environment, or banner.
 */
void init_shell() {
    // Any state you want to initialize (config files, env, etc.)
    // Example: Load AoT quotes, setup history, etc.
    printf("\033[1;32mInitializing grish(a)...\033[0m\n");
}

/**
 * Displays the prompt dynamically.
 */
void display_prompt() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char *user = getpwuid(getuid())->pw_name;

    printf("\033[1;34m%s\033[0m@\033[1;36mgrish(a)\033[0m:\033[1;33m%s\033[0m$ ", user, cwd);
    fflush(stdout);
}

/**
 * Reads a line of input from the user using getline.
 */
char *read_input() {
    char *line = NULL;
    size_t len = 0;

    ssize_t read = getline(&line, &len, stdin);

    if (read == -1) {
        free(line);
        return NULL;  // Handle EOF or Ctrl+D
    }

    // Trim newline character
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    return line;
}

/**
 * Optionally cleanup resources.
 */
void cleanup_shell() {
    // Free any allocated global resources, history, etc.
    // You can even print an AoT-themed goodbye message here
}


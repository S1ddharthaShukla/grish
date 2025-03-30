#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/utils.h"

#define SHELL_EXIT_CODE 999

/**
 * Executes external programs or built-in commands.
 * Returns:
 * - 0 on success
 * - SHELL_EXIT_CODE if shell should exit
 */
int execute_command(char **args) {
    if (args == NULL || args[0] == NULL) {
        return 0;
    }

    if (is_builtin(args[0])) {
        return execute_builtin(args);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("grish(a): fork failed");
        return -1;
    }

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            fprintf(stderr, "grish(a): command not found: %s\n", args[0]);
            print_random_levi_quote();  
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process waits
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 0;
}


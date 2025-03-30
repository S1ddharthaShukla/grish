// main.c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../include/shell.h"
#include "../include/utils.h"
#include "../include/executor.h"
#include "../include/parser.h"

void sigint_handler(int sig) {
    (void)sig;
    write(STDOUT_FILENO, "\nUse 'exit' or 'eren' to quit grish(a).\n", 40);
    display_prompt(); // Restore the prompt after Ctrl+C
    fflush(stdout);
}

int main(void) {
    // Setup AoT-themed banner and init
    clear_screen();
    print_banner();     // From utils.c
    init_shell();       // Shell state initialization (env, cwd, etc.)

    // Handle Ctrl+C
    signal(SIGINT, sigint_handler);

    // Main REPL loop
    while (1) {
        display_prompt();                  // grish(a)>
        char *input = read_input();        // Get user input

        if (input == NULL) {
            printf("\n");
            break;  // EOF or Ctrl+D
        }

        if (is_whitespace(input)) {
            free(input);
            continue;
        }

        char **args = parse_input(input);  // Tokenize input

        if (args != NULL && args[0] != NULL) {
            int status = execute_command(args);  // Fork or handle built-ins

            if (status == SHELL_EXIT) {
                free(input);
                free_args(args);
                break;
            }
        }

        free(input);
        free_args(args);
    }

    cleanup_shell();  // Optional: clear history, free env vars, etc.
    printf("Goodbye, soldier. \U0001F1F8\U0001F1EB\n"); // AoT outro
    return 0;
}


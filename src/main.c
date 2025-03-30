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
    clear_screen();
    print_banner(); 
    init_shell();      

    signal(SIGINT, sigint_handler);

    while (1) {
        display_prompt();                 
        char *input = read_input();      

        if (input == NULL) {
            printf("\n");
            break;  
        }

        if (is_whitespace(input)) {
            free(input);
            continue;
        }

        char **args = parse_input(input);  

        if (args != NULL && args[0] != NULL) {
            int status = execute_command(args);  

            if (status == SHELL_EXIT) {
                free(input);
                free_args(args);
                break;
            }
        }

        free(input);
        free_args(args);
    }

    cleanup_shell();  
    printf("Goodbye, soldier. \U0001F1F8\U0001F1EB\n"); 
    return 0;
}


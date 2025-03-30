// utils.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stddef.h>
#include "../include/utils.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

void clear_screen() {
    printf("\033[H\033[J");
    fflush(stdout);
}

void print_banner() {
    clear_screen();
    printf("\n");
    printf("\n");
    printf("     █████╗ ██████╗ ██╗███████╗██╗  ██╗ █████╗     \n");
    printf("    ██╔══  ╗██╔══██╗██║██╔════╝██║  ██║██╔══██╗    \n");
    printf("    ██║ ███║██████╔╝██║███████╗███████║███████║    \n");
    printf("    ██║  ██║██╔══██╗██║╚════██║██╔══██║██╔══██║    \n");
    printf("    ╚█████╔╝██║  ██║██║███████║██║  ██║██║  ██║    \n");
    printf("     ╚════╝ ╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝    \n");
    printf(WHITE "             Welcome to " CYAN "grish(a)" WHITE " Shell\n");
    printf("        Inspired by Grisha Yeager from AoT\n\n");
    printf(YELLOW "     Type 'help' to see available commands.\n");
    printf("     Fight for freedom.\n\n" RESET);
}

void free_args(char **args) {
    if (!args) return;
    for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
    free(args);
}

int is_whitespace(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

char *strndup_safe(const char *s, size_t n) {
    char *result = malloc(n + 1);
    if (!result) return NULL;
    strncpy(result, s, n);
    result[n] = '\0';
    return result;
}

void print_random_levi_quote() {
    const char *quotes[] = {
        "The only thing we're allowed to do is to believe we won't regret the choice we made.",
        "This world is merciless, and it's also very beautiful.",
        "If you don’t want to die, think.",
        "A lesson you learned from your enemies can’t be unlearned.",
        "Don’t die. Survive.",
        "We live in a cruel world.",
        "Give up on your dreams and die."
    };
    size_t count = sizeof(quotes) / sizeof(quotes[0]);

    // Initialize random once
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    int index = rand() % count;
    fprintf(stderr, RED "Levi:\033[0m %s\n", quotes[index]);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/parser.h"
#include "../include/utils.h"

#define INITIAL_ARGV_SIZE 8

/**
 * Tokenizes the input string into an argument array.
 * Handles:
 * - Quotes ("...")
 * - Escaped spaces (\ )
 * - Skips redundant whitespace
 */
char **parse_input(const char *input) {
    if (input == NULL) return NULL;

    int bufsize = INITIAL_ARGV_SIZE;
    int argc = 0;
    char **argv = malloc(bufsize * sizeof(char *));
    if (!argv) {
        perror("grish(a): malloc");
        return NULL;
    }

    const char *ptr = input;
    while (*ptr != '\0') {
        while (isspace((unsigned char)*ptr)) ptr++; // Skip leading spaces
        if (*ptr == '\0') break;

        char *token = NULL;

        // Handle quoted string
        if (*ptr == '\"') {
            ptr++;
            const char *start = ptr;
            while (*ptr && *ptr != '\"') {
                if (*ptr == '\\' && *(ptr + 1) == '\"') ptr++; // Handle escaped quote
                ptr++;
            }
            size_t len = ptr - start;
            token = strndup_safe(start, len);
            if (*ptr == '\"') ptr++;
        } 
        // Handle normal word or escaped spaces
        else {
            const char *start = ptr;
            while (*ptr && !isspace((unsigned char)*ptr)) {
                if (*ptr == '\\' && *(ptr + 1)) ptr++; // Skip escaped next char
                ptr++;
            }
            size_t len = ptr - start;
            token = strndup_safe(start, len);
        }

        if (token) {
            if (argc >= bufsize) {
                bufsize *= 2;
                argv = realloc(argv, bufsize * sizeof(char *));
                if (!argv) {
                    perror("grish(a): realloc");
                    return NULL;
                }
            }
            argv[argc++] = token;
        }
    }

    argv[argc] = NULL; // Null-terminate the array
    return argv;
}


// utils.h

#ifndef GRISHA_UTILS_H
#define GRISHA_UTILS_H

#include <stddef.h>
void clear_screen();
void print_banner();
void free_args(char **args);
char *strndup_safe(const char *s, size_t n);
int is_whitespace(const char *str);
void print_random_levi_quote();

#endif // GRISHA_UTILS_H


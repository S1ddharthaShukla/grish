// builtins.c
#define _DEFAULT_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <time.h>
#include <termios.h>
#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/utils.h"

// Built-in command declarations
int grisha_cd(char **args);
int grisha_exit(char **args);
int grisha_help(char **args);
int grisha_eren(char **args);
int grisha_yeager(char **args);
int grisha_rumbling(char **args);
int grisha_scouts(char **args);
int grisha_shifter(char **args);
int grisha_titan(char **args);
int grisha_paradis(char **args);

typedef struct {
    const char *name;
    int (*func)(char **args);
} Builtin;

Builtin builtins[] = {
    { "cd",      grisha_cd },
    { "exit",    grisha_exit },
    { "help",    grisha_help },
    { "eren",    grisha_eren },
    { "yeager",  grisha_yeager },
    { "shifter", grisha_shifter },
    { "titan",   grisha_titan },
    { "rumbling", grisha_rumbling },
    { "scouts",  grisha_scouts },
    { "paradis", grisha_paradis },
};

int num_builtins() {
    return sizeof(builtins) / sizeof(Builtin);
}

int is_builtin(const char *cmd) {
    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(cmd, builtins[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

int execute_builtin(char **args) {
    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            return builtins[i].func(args);
        }
    }
    return 0;
}

/* === Built-in Implementations === */

int grisha_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "grish(a): expected argument to \"cd\"\n");
    } else if (chdir(args[1]) != 0) {
        perror("grish(a)");
    }
    return 0;
}

int grisha_exit(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;31mEren:\033[0m If you want to leave the walls... go.\n");
    return SHELL_EXIT;
}

int grisha_help(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;32mWelcome to grish(a) - the AoT shell.\033[0m\n");
    printf("Available commands:\n");
    for (int i = 0; i < num_builtins(); i++) {
        printf("  - %s\n", builtins[i].name);
    }
    printf("\nType like a soldier. Fight like a Titan.\n");
    return 0;
}

int grisha_eren(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;31mEren Yeager:\033[0m I'll destroy them... every last one of them.\n");
    return SHELL_EXIT;
}

int grisha_yeager(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;33mGrisha Yeager:\033[0m To save Mikasa... Armin... and everyone else...\n");
    printf("You must fight.\n");
    return 0;
}

int grisha_shifter(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;35mShifter:\033[0m You possess the power of the Titans.\n");
    printf("Available forms:\n");
    printf("  - Attack Titan\n  - Founding Titan\n  - Colossal Titan\n");
    return 0;
}

int grisha_rumbling(char **args) {
    (void)args;

    const char *frames[] = {
        "🔥🔥🔥 THE RUMBLING 🔥🔥🔥",
        "🔥🔥🔥  THE RUMBLING 🔥🔥🔥",
        "🔥🔥🔥   THE RUMBLING 🔥🔥🔥",
        "🔥🔥🔥    THE RUMBLING 🔥🔥🔥",
        "🔥🔥🔥     THE RUMBLING 🔥🔥🔥",
    };
    int num_frames = sizeof(frames) / sizeof(frames[0]);

    for (int i = 0; i < 20; i++) {
        printf("\033[H\033[J"); // Clear screen
        printf("\n\n\n\t\t%s\n", frames[i % num_frames]);
        fflush(stdout);
        usleep(70000); // Small delay
    }

    printf("\033[H\033[J"); // Final clear
    return 1;
}

int grisha_scouts(char **args) {
    (void)args;

    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("grisha: scouts");
        return 1;
    }

    printf("📋 Active Scouts (Processes):\n");
    printf("%-10s %-30s\n", "PID", "CMD");

    struct dirent *entry;
    while ((entry = readdir(proc)) != NULL) {
        if (!isdigit(entry->d_name[0])) continue;

        char path[512], cmdline[256];
        snprintf(path, sizeof(path), "/proc/%s/cmdline", entry->d_name);

        FILE *cmdf = fopen(path, "r");
        if (cmdf) {
            fgets(cmdline, sizeof(cmdline), cmdf);
            fclose(cmdf);

            if (strlen(cmdline) == 0)
                strcpy(cmdline, "[kernel]");

            printf("%-10s %-30s\n", entry->d_name, cmdline);
        }
    }

    closedir(proc);
    return 1;
}

int grisha_titan(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;31mTitan Form Activated!\033[0m ROOOAAARRRR!!! 💥💥\n");
    return 0;
}

int grisha_paradis(char **args) {
    (void)args; // Unused parameter
    printf("\033[1;34mParadis Island:\033[0m Welcome to the last stronghold of humanity.\n");
    return 0;
}


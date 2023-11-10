#ifndef FUNCTION_H
#define FUNCTION_H 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void prompt(char **env);
void print_environment(char **env);
void handle_env(char **env);
void handle_unsetenv(char **argv);
void handle_setenv(char **argv);

#endif

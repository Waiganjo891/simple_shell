#ifndef FUNCTION_H
#define FUNCTION_H 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void prompt(char **av, char **env);
void print_env(char **env);
void execute_command(char **argv, char **env);

#endif

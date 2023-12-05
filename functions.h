#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

char *get_command_path(char *command);

#endif

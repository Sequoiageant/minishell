#ifndef MSHELL_H
# define MSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
#define BUF_SIZE 1000

int ms_echo(int argc, char *argv[]);

#endif

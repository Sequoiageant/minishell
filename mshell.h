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

typedef int (*t_built)(int argc, char *argv[]);
int ms_echo(int argc, char *argv[]);
int ms_cd(int argc, char *argv[]);
int ms_pwd(int argc, char *argv[]);
int ms_export(int argc, char *argv[]);
int ms_env(int argc, char *argv[]);
int ms_unset(int argc, char *argv[]);
int ms_exit(int argc, char *argv[]);
int ft_fork(char **cmd);
int ft_built_in(char **cmd, int argc, int index);
int ft_traitement(char **cmd);

#endif

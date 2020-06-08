#include "libft.h"
#include "mshell.h"

int ft_fork(char **cmd)
{
    pid_t new_pid;
    int status;
    
    new_pid = fork();
    if (new_pid == 0)
    {
        // new process
        ft_putstr_fd(">>Inside new process\n", 1);
        // va chercher ./cmd[0] pour l'executer
        // il faudrait au préalable chercher dans PATH pour trouver l'executable correspondant à la commande. Puis donner le "chemin" de cet executable en input (à la place de cmd[0])
        if (execve(cmd[0], cmd, NULL) == -1)
            printf(">>Exec failed\n");
        // else should not return
    }
    else
    {
        // old process
        wait(&status);
        return(new_pid);
    }
    
}
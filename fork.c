#include "libft.h"
#include "mshell.h"

int ft_fork(char **cmd)
{
    pid_t new_pid;
    int status;
    char *filepath;
    filepath = ft_calloc(100, 1);
    
    new_pid = fork();
    if (new_pid == 0)
    {
        // new process
        ft_putstr_fd(">>Inside new process\n", 1);
        // va chercher ./cmd[0] pour l'executer
        // il faudrait au préalable chercher dans PATH pour trouver l'executable correspondant à la commande. Puis donner le "chemin" de cet executable en input (à la place de cmd[0])
        ft_strlcat(filepath, "executables/", 100);
        ft_strlcat(filepath, cmd[0], 100);
        printf("filename: %s\n", filepath);
        if (execve(filepath, cmd, NULL) == -1)
            printf(">>Exec failed\n");  
        // else should not return
    }
    else
    {
        // old process
        wait(&status);
        // return(new_pid);
    }
    free(filepath);
    return(0);
}
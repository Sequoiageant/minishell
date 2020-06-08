#include "libft.h"
#include "mshell.h"

int ft_check_built_in(char *cmd, int *index)
{
    char *built[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int i;
    unsigned int len_cmd;
    int max_len;
    int res;

    // index: index du built_in correspondant à la commande, au sein du tableau "built"
    len_cmd = ft_strlen(cmd);
    i = 0;
    while (built[i])
    {
        if (len_cmd > ft_strlen(built[i]))
            max_len = len_cmd;
        else
            max_len = ft_strlen(built[i]);
        if ((res = ft_strncmp(cmd, built[i], max_len) == 0))
        {
            *index = i;
            return (TRUE);
        }
        i++;
    }
    return (FALSE);
}

int ft_traitement(char **cmd)
{    
    int argc;
    int built_index;
    
    // cas 1: la commande appelée est une commande built-in -> executée directement dans notre programme
    // cas 2: pas un built-in: on veut créer un nouveau process pour l'executer, via fork
    // --> avant de faire le fork, on vérifie que la fonction n'est pas un shell built-in
    argc = 0;
    while (cmd[argc])
        argc++;
    if (ft_check_built_in(cmd[0], &built_index) == TRUE)
    {
        ft_putstr_fd(">>built-in\n", 1);
        ft_built_in(cmd, argc, built_index);
        // lance la fonction "cmd";
    }
    else
    {
        ft_putstr_fd(">>fork\n", 1);
        ft_fork(cmd);
    }
    return(0);
}
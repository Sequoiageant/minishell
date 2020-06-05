#include "libft.h"
#include "mshell.h"

int ft_check_built_in(char *cmd, int *index)
{
    char *built[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int i;
    int len_cmd;
    int max_len;
    int res;

    *index = -1;
    i = 0;
    while (built[i])
    {
        if (len_cmd > ft_strlen(built[i]))
            max_len = len_cmd;
        else
            max_len = ft_strlen(built[i]);
        if ((res = ft_strncmp(cmd, built[i], max_len)) == 0)
        {
            *index = i;
            return (TRUE);
        }
        i++;
    }
    return (FALSE);
}

int ft_exec_built(char **cmd, int argc, int index)
{
    if (index == 0)
        ms_echo(argc, cmd);
    else
        ft_putstr_fd("function not written yet\n", 1);
}

int ft_fork(char **cmd)
{
    pid_t new_pid;
    
    new_pid = fork();
    if (new_pid == 0)
    {
        ft_putstr_fd("Inside new process\n", 1);
        if (execve(cmd[0], cmd, NULL) == -1)
            printf("exec failed\n");
    }
}

int ft_handle(char *buf)
{
    char **cmd;
    int argc;
    int built_index;

    cmd = ft_split(buf, ' ');
    // cas 1: la commande appelée est une commande built-in -> executée directement dans notre programme
    // cas 2: pas un built-in: on veut créer un nouveau process pour l'executer, via fork
    // avant de faire le fork, vérifier que la fonction n'est pas un shell built-in
    argc = 0;
    while (cmd[argc])
        argc++;
    if (ft_check_built_in(cmd[0], &built_index) == TRUE)
    {
        ft_putstr_fd("built-in\n", 1);
        ft_exec_built(cmd, argc, built_index);
        // lance la fonction "cmd";
    }
    else
    {
        ft_putstr_fd("fork\n", 1);
        ft_fork(cmd);
    }
    
    // int i = 0;
    // while (cmd[i])
    // {
    //     // ft_putnbr_fd(i, 1);
    //     // ft_putstr_fd("\n", 1);
    //     ft_putstr_fd(cmd[i], 1);
    //     // ft_putstr_fd("\n", 1);
    //     i++;
    // }
    
    // free cmd
    
}

int main()
{        
    int ret;
    char *buf;
    buf = malloc(BUF_SIZE + 1);

    ft_putstr_fd("Welcome to shell: \n", 1);
    while(1)
    {
        ft_putstr_fd("cmd: ", 1);
        ret = read(1, buf, BUF_SIZE);
        // on a un /n qui s'ajoute à la fin du buffer, dont on ne veut pas
        if (ret)
            buf[ret - 1] = 0;
        else
            buf[ret] = 0;
        ft_handle(buf);
    }
}
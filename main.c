#include "libft.h"
#include "mshell.h"

void ft_print_env(t_list *env)
{
    t_key_val *elem;
    
    while (env)
    {
        elem = (t_key_val *)(env->content);
        printf("clé: %s\n", elem->key);
        printf("val: %s\n", elem->val);
        env = env->next;
    }
}

void print_cmd(char **cmd)
{
    int i = 0;
    while (cmd[i])
    {
        // ft_putnbr_fd(i, 1);
        // ft_putstr_fd("\n", 1);
        ft_putstr_fd(cmd[i], 1);
        // ft_putstr_fd("\n", 1);
        i++;
    }
}

int ft_handle(char *buf)
{
    char **cmd;

    // il faudrait parser ici la commande, et set des flags en fonction (chercher les '<', '>>'...)
    cmd = ft_split(buf, ' ');
    // ft_parse(buf);
    ft_traitement(cmd);
    //free cmd
    return(0);
}

int main()
{        
    t_list *env;
    int ret;
    char *buf;
    buf = malloc(BUF_SIZE + 1);

    ft_init(&env);
    ft_print_env(env);
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
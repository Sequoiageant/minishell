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

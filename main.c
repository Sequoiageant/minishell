#include "libft.h"
#include "mshell.h"

int ft_handle(char *buf)
{
    char **cmd;

    // il faudrait parser ici la commande, et set des flags en fonction (chercher les '<', '>>'...)
    cmd = ft_split(buf, ' ');
    // ft_parse(buf);
    ft_traitement(cmd);
    int i = 0;
    
    while (cmd[i])
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);

    return(0);
}

void del(void *elem)
{
    t_key_val *key_val;

    key_val = (t_key_val*)elem;
    
    free(key_val->key);
    free(key_val->val);
    free(key_val);
}

int main()
{        
    t_list *env;
    int ret;
    char *buf;

    buf = malloc(BUF_SIZE + 1);
    ft_init(&env);
    // ft_print_env(env);
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
    ft_lstclear(&env, &del);
    free(buf);
}
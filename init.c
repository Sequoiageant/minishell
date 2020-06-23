#include "libft.h"
#include "mshell.h"


char **ft_split_env(char *key_val)
{
    char **elem;
    int i;
    int j;

    elem = malloc(2 * sizeof(char *));
    i = 0;
    while (key_val[i] && key_val[i] != '=')
        i++;
    elem[0] = malloc((i + 1) * sizeof(char));
    i = 0;
    while (key_val[i] && key_val[i] != '=')
    {
        elem[0][i] = key_val[i];
        i++;
    }
    elem[0][i] = 0;
    elem[1] = malloc(ft_strlen(key_val) - i);
    i++;
    j = 0;
    while (key_val[i])
    {
        elem[1][j] = key_val[i];
        i++;
        j++;
    }
    elem[1][j] = 0;
    return (elem);
}

int ft_init(t_list **env)
{
    extern char **environ;
    char **elem;
    t_key_val *key_val;
    int i;

    ft_putstr_fd("Welcome to Bash\n", 1);
    *env = NULL;
    i = 0;
    while(environ[i])
    {
        // printf("%s\n", environ[i]);
        elem = ft_split_env(environ[i]);
        key_val = malloc(sizeof(t_key_val));
        key_val->key = elem[0];
        key_val->val = elem[1];
        ft_lstadd_back(env, ft_lstnew(key_val));
        free(elem);
        i++;
    }
    return(0);
}
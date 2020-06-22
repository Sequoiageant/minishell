#include "libft.h"
#include "mshell.h"

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
        elem = ft_split(environ[i], '='); // il faudrait créer un split customisé qui spliterait en deux. Délimiteur = premier '='
        key_val = malloc(sizeof(key_val));
        key_val->key = elem[0];
        key_val->val = elem[1];
        ft_lstadd_back(env, ft_lstnew(key_val));
        free(elem[2]);
        free(elem);
        i++;
    }
    return(0);
}
#include "libft.h"
#include "mshell.h"

int ft_built_in(char **cmd, int argc, int index)
{
    t_built built_func[] = {ms_echo, ms_cd}; // ,ms_pwd, ms_export, ms_unset, ms_env, ms_exit};
    int ret;

    if (index < 2)
        ret = built_func[index](argc, cmd);
    else
        ft_putstr_fd("function not written yet\n", 1);
    return(ret);
}
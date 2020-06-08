#include "libft.h"
#include "mshell.h"

int ft_built_in(char **cmd, int argc, int index)
{
    if (index == 0)
        ms_echo(argc, cmd);
    else
        ft_putstr_fd("function not written yet\n", 1);
    return(0);
}
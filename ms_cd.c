#include "libft.h"
#include "mshell.h"

int ms_cd(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    ft_putstr_fd("ms_cd built-in\n", 1);
    return(0);
}
#include "libft.h"
#include "mshell.h"

int ft_built_in(char **cmd, int argc, int index)
{
    t_built built_func[] = {ms_echo, ms_cd}; // ,ms_pwd, ms_export, ms_unset, ms_env, ms_exit};
    int ret;
    // char *cwd = NULL;

    if (index < 2)
    {
        // printf("pre-pwd: %s\n", getenv("PWD"));
        // printf("pre-getcwd: %s\n", getcwd(cwd, 200));
        ret = built_func[index](argc, cmd);
        // printf("post-pwd: %s\n", getenv("PWD"));
        // printf("post-getcwd: %s\n", getcwd(cwd, 200));
        // free(cwd);
    }
    else
        ft_putstr_fd("function not written yet\n", 1);
    return(ret);
}
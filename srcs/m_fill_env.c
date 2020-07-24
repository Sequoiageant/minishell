
#include "libft.h"
#include "mshell.h"


int fill_env_cmd(t_cmd *cmd, t_list *env, int exit_code)
{
    char    *str;
    t_list  *flag;
    int     i;
    int     j;

    j = 0;
    flag = cmd->flag;
    while (cmd->argv[j])
    {
        str = cmd->argv[j];
        i = 0;
        while (str[i])
        {
            if (str[i] == '$')
            {
                if (*(int *)flag->content == TRUE)
                {    
                    (void) env;
                    (void)exit_code;
                    // substitute(str, env, exit_code);
                }
                flag = flag->next;
            }
            i++;
        }
        j++;
    }
    return (SUCCESS);
}

int fill_env(t_list *pipe, t_list *env, int exit_code)
{
    t_cmd *cmd;
    while (pipe)
    {
        cmd = (t_cmd*)pipe->content;
        fill_env_cmd(cmd, env, exit_code); // on fill chaque cmd du pipe
        pipe = pipe->next;
    }
    return (SUCCESS);
}
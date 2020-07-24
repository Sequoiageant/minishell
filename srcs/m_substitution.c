
#include "libft.h"
#include "mshell.h"


void	ft_realloc(char **new, char **src)
{
	if (new == NULL)
		return ;
	if (*src)
	{
		free(*src);
		*src = NULL;
		*src = *new;
	}
}


int		substitute_dollar(char **str, t_list *env)
{
	int			i;
	char		*tmp;
	t_key_val	*key_val;
	char		*ret;

	i = count_dollar_char(*str);
	tmp = ft_substr(*str, 1, i);
	if (tmp)
	{
		if (tmp[0] == '?')
			ret = ft_itoa(g_glob.ret);
		else
		{
			key_val = find_key_val(env, tmp);
			ret = ft_strdup(key_val->val);
		}
		ft_realloc(&ret, str);
		free(tmp);
	}
	return (SUCCESS);
}

void	ft_substitute(char **str, t_list *env, t_list *flag)
{
	(void) env;
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (*(int *)flag->content == TRUE)
			{
				substitute_dollar(str, env);
			}
			flag = flag->next;
		}
		i++;
	}
}

int substitute_cmd(t_cmd *cmd, t_list *env)
{
	t_list	*flag;
	int		i;
	char	**arg;

	i = 0;
	flag = cmd->flag;
	arg = cmd->argv;
	while (arg[i])
	{
		ft_substitute(&arg[i], env, flag);
		i++;
	}
	return (SUCCESS);
}

int ft_substitution(t_list *cmd_list, t_list *env)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		substitute_cmd(cmd, env); // on fill chaque cmd du pipe
		// substitute_redirs(cmd, env, exit_code); // on fill chaque cmd du pipe
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
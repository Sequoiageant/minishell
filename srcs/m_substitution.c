
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
			if (key_val)
				ret = ft_strdup(key_val->val);
			else
				ret = ft_strdup("");
		}
		ft_realloc(&ret, str);
		free(tmp);
	}
	return (SUCCESS);
}

void	ft_substitute(char **str, t_list *env, t_list *flag)
{
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

int substitute_cmd(char **argv, t_list	*flag, t_list *env)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		ft_substitute(&argv[i], env, flag);
		i++;
	}
	return (SUCCESS);
}

int substitute_redirs(t_list *redir_lst, t_list	*flag, t_list *env)
{
	t_redir	*redir;

	while (redir_lst)
	{
		redir = (t_redir *)redir_lst->content;
		ft_substitute(&redir->file, env, flag);
		redir_lst = redir_lst->next;
	}
	return (SUCCESS);
}

int ft_substitution(t_list *cmd_list, t_list *env)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		substitute_cmd(cmd->argv, cmd->flag, env); // on fill chaque cmd du pipe
		substitute_redirs(cmd->redir, cmd->flag_redir, env); // on fill chaque cmd du pipe
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
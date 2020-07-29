
#include "libft.h"
#include "mshell.h"


size_t	ft_strchr_pos(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	ft_realloc(char **new, char **src)
{
	if (new == NULL || src == NULL)
		return ;
	if (*src)
	{
		free(*src);
		*src = NULL;
		*src = *new;
	}
}

size_t	substitute_dollar(char **str, t_list *env)
{
	size_t		i;
	char		*tmp;
	char		*ret;
	t_key_val	*key_val;

	ret = NULL;
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
		if (ret)
			ft_realloc(&ret, str);
		free(tmp);
	}
	return (i);
}

int	ft_handle_argv(char **tmp, t_list *env, t_list **flag, char c)
{
	size_t	len;

	len = 0;
	if (c == '$')
	{
		if (*(int *)(*flag)->content == TRUE)
			len = substitute_dollar(tmp, env);
		else
			len = ft_strlen(*tmp) - 1;
		(*flag) = (*flag)->next;
	}
	else
		len = ft_strlen(*tmp) - 1;
	return (len);
}

void	ft_substitute(char **str, t_list *env, t_list *flag)
{
	size_t	i;
	size_t	len;
	char	*tmp;
	char	*final;

	i = 0;
	tmp = NULL;
	final = NULL;
	while ((*str)[i])
	{
		len = 0;
		tmp = ft_substr(*str, i, ft_strchr_pos(*str + i + 1, '$') + 1);
		if (tmp)
		{
			len = ft_handle_argv(&tmp, env, &flag, (*str)[i]);
			ft_strjoin_back(tmp, &final);
			free(tmp);
		}
		i+=(len + 1);
	}
	if (final)
	{
		if (ft_strlen(final) == 0)
		{
			ft_str_free(str);
			ft_str_free(&final);
		}
		else
			ft_realloc(&final, str);
	}
}

void	lst_delone_argv(t_list **argv_list)
{
	t_list		*tmp;
	t_list		*before;
	int			i;

	before = *argv_list;
	tmp = *argv_list;
	i = 0;
	while (tmp)
	{
		if (tmp->content == NULL)
		{
			if (i == 0)
			{
				before = tmp->next;
				*argv_list = before;
			}
			else
				before->next = tmp->next;
			del_argv_node(&tmp);
			return ;
		}
		i++;
		before = tmp;
		tmp = tmp->next;
	}
}

int substitute_cmd(t_list *argv_list, t_list	*flag, t_list *env)
{
	char	**argv;
	t_list	*tmp;

	tmp = argv_list;
	while (tmp)
	{
		argv = (char **)&tmp->content;
		ft_substitute(argv, env, flag);
		tmp = tmp->next;
	}
	// ft_print_argv_list(argv_list);
	lst_delone_argv(&argv_list);
	// ft_print_argv_list(argv_list);
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

/*t_list	*tab_to_list(char **argv)
{
	t_list	*argv_list;
	size_t	i;

	i = 0;
	argv_list = NULL;
	while (argv[i])
	{
		ft_lstadd_back(&argv_list, ft_lstnew(ft_strdup(argv[i])));
		i++;
	}
	return (argv_list);
}*/

int ft_substitution(t_list *cmd_list, t_list *env)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		substitute_cmd(cmd->argv_list, cmd->flag, env);
		substitute_redirs(cmd->redir, cmd->flag_redir, env);
		if (cmd->argv_list)
			cmd->argv = ft_list_to_tab_argv(cmd->argv_list);
		cmd->argc = ft_lstsize(cmd->argv_list);
		if (cmd->argv[0]) // si NULL cause un segfault
		{
			if (fill_cmd_path(cmd, env) == FAILURE)
				return (FAILURE);
		}
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}
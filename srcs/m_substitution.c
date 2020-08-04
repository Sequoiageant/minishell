/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_substitution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:04:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/04 18:08:26 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	preserve_quotes(char **str)
{
	char *tmp;
	char *new;
	int i;

	if (*str == NULL)
		return ;
	i = 0;
	tmp = *str;
	new = ft_strdup(""); // on initialise new
	while (tmp[i])
	{
		if (tmp[i] == '"' || tmp[i] == '\'' || tmp[i] == '\\')
			ft_join_to_str(char_to_str('\\'), &new);
		ft_join_to_str(char_to_str(tmp[i]), &new);
		i++;
	}
	free(*str);
	*str = new;
}


void	ft_realloc_or_free(char **final, char **src)
{
	if (ft_strlen(*final) == 0)
	{
		ft_str_free(src);
		ft_str_free(final);
	}
	else
		ft_realloc(final, src);
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
			{
				preserve_quotes(&key_val->val); // escape single quotes, double quotes and backslashes, if not they will be lost during "clean_quotes"
				ret = ft_strdup(key_val->val);
			}
			else
				ret = ft_strdup("");
		}
		if (ret)
			ft_realloc(&ret, str);
		free(tmp);
	}
	return (i);
}

/*int	ft_handle_argv(char **tmp, t_list *env, t_list **flag, char c)
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
*/
int		ft_substitute(char **str, t_list *env, t_list **flag)
{
	size_t	i;
	size_t	len;
	char	*tmp;
	char	*final;
	int		ret;

	i = 0;
	tmp = NULL;
	final = NULL;
	ret = FALSE;
	while ((*str)[i])
	{
		len = 0;
		tmp = ft_substr(*str, i, ft_strchr_pos(*str + i + 1, '$') + 1);
		if (tmp)
		{
			if ((*str)[i] == '$')
			{
				if (*(int *)(*flag)->content == TRUE)
				{
					len = substitute_dollar(&tmp, env);
					ret = TRUE;
				}
				else
					len = ft_strlen(tmp) - 1;
				(*flag) = (*flag)->next;
			}
			else
				len = ft_strlen(tmp) - 1;
			ft_strjoin_back(tmp, &final);
			free(tmp);
		}
		i+=(len + 1);
	}
	if (final)
		ft_realloc_or_free(&final, str);
	return (ret);
}

/*void	lst_del_null_nodes(t_list **list)
{
	t_list		*tmp;
	t_list		*before;
	int			i;

	before = *list;
	tmp = *list;
	i = 0;
	while (tmp)
	{
		if (tmp->content == NULL)
		{
			if (i == 0)
			{
				before = tmp->next;
				*list = before;
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
}*/

size_t	tab2_size(char **tab)
{
	size_t			i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	free_tab2(tab);
	return (i);
}

void	ft_tab_to_list(t_list **list, char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(tab[i])));
		i++;
	}
	free_tab2(tab);
}

int		is_even(int nb)
{
	return ((nb % 2) == 0);
}

int		is_splittable(char *argv)
{
	size_t	i;
	int		count_before;
	int		count_after;

	i = 0;
	count_before = 0;
	count_after = 0;
	while(argv[i] && argv[i] != '$')
	{
		if (argv[i] == '"')
			count_before++;
		i++;
	}
	i++;
	while(argv[i] && argv[i] != '$')
	{
		if (argv[i] == '"')
			count_after++;
		i++;
	}
	if (is_even(count_before) && is_even(count_after))
		return (TRUE);
	return (FALSE);
}

t_list *substitute_argv(t_list *argv_list, t_list *flag, t_list *env)
{
	char	**argv;
	char	*argv_cpy;
	t_list	*new_argv_list;

	new_argv_list = NULL;
	while (argv_list)
	{
		argv = (char **)&argv_list->content;
		argv_cpy = ft_strdup(*argv);
		if (ft_substitute(argv, env, &flag))
		{
			if (*argv)
			{
				if (is_splittable(argv_cpy))
					ft_tab_to_list(&new_argv_list, ft_split_wp(*argv));
				else
					ft_lstadd_back(&new_argv_list, ft_lstnew(ft_strdup(*argv)));
			}
		}
		else
			ft_lstadd_back(&new_argv_list, ft_lstnew(ft_strdup(*argv)));
		argv_list = argv_list->next;
		ft_str_free(&argv_cpy);
	}
	return (new_argv_list);
}

int substitute_redirs(t_list **redir_lst, t_list *flag, t_list *env)
{
	t_redir	*redir;
	t_list	*tmp;
	size_t	file_count;

	tmp = *redir_lst;
	file_count = 0;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		redir->original = ft_strdup(redir->file);
		if (ft_substitute(&redir->file, env, &flag))
		{
			if (redir->file)
			{
				if (is_splittable(redir->original))
				{
					file_count = tab2_size(ft_split_wp(redir->file));
					if (file_count > 1)
						redir->state = FAILURE;
				}
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int ft_expansion(t_list *cmd_list, t_list *env)
{
	t_cmd	*cmd;
	t_list	*new_argv_list;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		new_argv_list = substitute_argv(cmd->argv_list, cmd->flag, env);
		substitute_redirs(&cmd->redir, cmd->flag_redir, env);
		cmd->argv = ft_list_to_tab_argv(new_argv_list);
		cmd->argc = ft_lstsize(new_argv_list);
		ft_lstclear(&new_argv_list, &del_argv_list_elem);
		// if (cmd->argv[0])
		// {
		// 	if (fill_cmd_path(cmd, env) == FAILURE)
		// 		return (FAILURE);
		// }
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

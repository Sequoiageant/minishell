/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_expansion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:04:11 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/06 11:01:03 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int		ft_substitute(char **str, t_list *env, t_list **flag)
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
		tmp = ft_substr(*str, i, ft_strclen(*str + i + 1, '$') + 1);
		if (tmp)
		{
			len = ft_handle_argv(&tmp, env, flag, &ret);
			ft_strjoin_back(tmp, &final);
			ft_str_free(&tmp);
		}
		i += (len + 1);
	}
	if (final)
		ft_realloc_or_free(&final, str);
	return (ret);
}

static int		is_splittable(char *argv)
{
	size_t	i;
	size_t	count_before;
	size_t	count_after;

	i = 0;
	count_before = 0;
	count_after = 0;
	while (argv[i] && argv[i] != '$')
	{
		if (argv[i] == '"')
			count_before++;
		i++;
	}
	i++;
	while (argv[i] && argv[i] != '$')
	{
		if (argv[i] == '"')
			count_after++;
		i++;
	}
	if (is_even(count_before) && is_even(count_after))
		return (TRUE);
	return (FALSE);
}

static t_list	*substitute_argv(t_list *argv_list, t_list *flag, t_list *env)
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

static int		substitute_redirs(t_list **rdr_lst, t_list *flag, t_list *env)
{
	t_redir	*redir;
	t_list	*tmp;
	size_t	file_count;

	tmp = *rdr_lst;
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

int				ft_expansion(t_list *cmd_list, t_list *env)
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
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

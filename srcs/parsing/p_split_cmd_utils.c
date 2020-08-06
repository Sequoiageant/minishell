/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:58:19 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:23:23 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int	set_redir_state(char *buf, int *state)
{
	int ret;

	if (buf[0] == '>' && buf[1] == '>')
	{
		ret = 2;
		*state = REDIR_APPEND;
	}
	else
	{
		if (buf[0] == '>')
			*state = REDIR_OUT;
		if (buf[0] == '<')
			*state = REDIR_IN;
		ret = 1;
	}
	while (buf[ret] == 9 || buf[ret] == 32)
		ret++;
	return (ret);
}

int	ft_join_to_str(char *added_str, char **initial_str)
{
	char *tmp;

	tmp = *initial_str;
	if ((*initial_str = ft_strjoin(tmp, added_str)) == NULL)
		return (FAILURE);
	free(tmp);
	free(added_str);
	return (SUCCESS);
}

int	ft_join_to_redir(char *added_str, t_list *redir_list)
{
	t_redir	*redir;

	while (redir_list->next)
		redir_list = redir_list->next;
	redir = (t_redir*)redir_list->content;
	ft_join_to_str(added_str, &redir->file);
	return (SUCCESS);
}

int	ft_join_to_argv(char *added_str, t_cmd *cmd)
{
	t_list	*tmp;

	if (ft_lstsize(cmd->argv_list) == 0)
		ft_lstadd_back(&cmd->argv_list, ft_lstnew(ft_strdup("")));
	tmp = cmd->argv_list;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->content == NULL)
	{
		tmp->content = (char*)added_str;
	}
	else
		ft_join_to_str(added_str, (char **)&tmp->content);
	return (SUCCESS);
}

int	ft_set_env_flag(t_cmd *cmd, int val, int where)
{
	int		*ptr_val;

	ptr_val = malloc(sizeof(int));
	*ptr_val = val;
	if (where == ARGV)
		ft_lstadd_back(&cmd->flag, ft_lstnew(ptr_val));
	if (where == REDIR)
		ft_lstadd_back(&cmd->flag_redir, ft_lstnew(ptr_val));
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_del2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:35:55 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 19:02:22 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void		del_pipe(void *elem)
{
	t_list *cmd_list;

	cmd_list = (t_list*)elem;
	ft_lstclear(&cmd_list, &del_cmd);
}

void		del_argv_list_elem(void *elem)
{
	char	*str;

	str = (char*)elem;
	free(str);
	str = NULL;
}

static void	del_redir(void *elem)
{
	t_redir	*redir;

	redir = (t_redir *)elem;
	free(redir->file);
	redir->file = NULL;
	if (redir->original)
	{
		free(redir->original);
		redir->original = NULL;
	}
	free(redir);
}

static void	del_flag(void *elem)
{
	int	*flag;

	flag = (int*)elem;
	free(flag);
	flag = NULL;
}

void		del_cmd(void *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)elem;
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	free(cmd->buf);
	cmd->buf = NULL;
	ft_lstclear(&cmd->redir, &del_redir);
	ft_lstclear(&cmd->flag, &del_flag);
	ft_lstclear(&cmd->flag_redir, &del_flag);
	free_tab2(cmd->argv);
	ft_lstclear(&cmd->argv_list, &del_argv_list_elem);
	free(cmd);
	cmd = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_buf_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:34:48 by grim              #+#    #+#             */
/*   Updated: 2020/08/06 09:39:22 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->argv = NULL;
	cmd->cmd_path = NULL;
	cmd->argc = 0;
	cmd->buf = malloc(1);
	cmd->buf[0] = 0;
	cmd->redir = NULL;
	cmd->flag = NULL;
	cmd->flag_redir = NULL;
	cmd->argv_list = NULL;
}

int		add_cmd(t_list *pipe_list)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	while (pipe_list->next)
		pipe_list = pipe_list->next;
	cmd_list = (t_list*)pipe_list->content;
	if ((cmd = malloc(sizeof(*cmd))) == NULL)
		return (FAILURE);
	ft_init_cmd(cmd);
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	if (pipe_list->content == NULL)
		pipe_list->content = cmd_list;
	return (SUCCESS);
}

void	delete_bn(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\n')
			(*str)[i] = '\0';
		i++;
	}
}

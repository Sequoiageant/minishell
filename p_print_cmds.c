/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_print_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:29:46 by grim              #+#    #+#             */
/*   Updated: 2020/07/02 17:31:02 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	print_pipe_bufs(t_list *pipe_list)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	cmd_list = (t_list*)pipe_list->content;
	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		printf("buf: [%s]\n", cmd->buf);
		cmd_list = cmd_list->next;
	}
}

void	print_pipe_argv_redirs(t_list *pipe_list)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	int		i;
	int		num;

	num = 0;
	cmd_list = (t_list*)pipe_list->content;
	while (cmd_list)
	{
		printf("CMD %d > \n", num);
		cmd = (t_cmd*)cmd_list->content;
		i = 0;
		while (cmd->argv[i])
		{
			printf(" argv[%d]: [%s]\n", i, cmd->argv[i]);
			i++;
		}
		if (cmd->input_file)
		{
			printf(" redir: input_file");
			printf(" file: [%s]\n", cmd->file);
		}
		if (cmd->output_file)
		{
			printf(" redir: output_file");
			printf(" file: [%s]\n", cmd->file);
		}
		if (cmd->output_file_append)
		{
			printf(" redir: output_file append");
			printf(" file: [%s]\n", cmd->file);
		}
		num++;
		cmd_list = cmd_list->next;
	}
}

void	print_commands(t_list *pipe_list)
{
	int i;

	i = 0;
	while (pipe_list)
	{
		printf("PIPE %d >> \n", i);
		// print_pipe_bufs(pipe_list);
		print_pipe_argv_redirs(pipe_list);
		pipe_list = pipe_list->next;
		i++;
	}
}

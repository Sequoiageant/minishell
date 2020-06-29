/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/06/29 15:21:10 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// int	ft_count_cmd(char *buf)
// {
// 	// separators = ; ou |		
// }

// int ft_detect_error(char *buf)
// {
// 	// exemple de syntax errors:
// 	//	[ < ]
// 	//	[ cmd < ] 
// }

// int	ft_subsitute(char **buf, t_list *env)
// {
//	// susbtituer les variables d'env
//	// gerer les '\'	
// }

int	ft_alloc_cmd(int num, t_list **cmd_list)
{
	int i;
	t_cmd *cmd;
	
	*cmd_list = NULL;
	i = 0;
	while (i < num)
	{
		cmd = malloc(sizeof(t_cmd));
		ft_lstadd_back(cmd_list, ft_lstnew(cmd));
		i++;
	}
	return (0);
}

int ft_init_cmd(t_list *cmd_list)
{
	t_cmd *cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		cmd->argc = 0;
		cmd->chained_input = 0;
		cmd->chained_output = 0;
		cmd->input_file = 0;
		cmd->output_file = 0;
		cmd->output_file_append = 0;
		cmd->argv = NULL;
		cmd->file = NULL;
		cmd_list = cmd_list->next;
	}
	return(0);
}

int	ft_parse(char *buf, t_list *env, t_list **cmd)
{
	int	num_cmd;
// 	int err;

	(void)env;

// 	ft_substitute(&buf, env);

// 	if ((err = ft_detect_error(buf) != 0))
// 	{
// 		ft_display_synthax_error(err);
// 		return(1);
// 	}

// 	num_cmd = ft_count_cmd(buf);
	num_cmd = 1;

	ft_alloc_cmd(num_cmd, cmd);
	ft_init_cmd(*cmd);
	ft_fill_cmd(*cmd, buf);
	return (0);
}
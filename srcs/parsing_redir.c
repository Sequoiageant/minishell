/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/07/28 11:06:42 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

static int		backslash_activated(char *buf, t_fsm_redir *machine)
{
	if (machine->flag_quote)
		return (0);
	if (machine->flag_dquote)
	{
		if (buf[1] == '$' || buf[1] == '"' || buf[1] == '\\')
			return (1);
		else
			return (0);
	}
	return (1);
}

static void		chose_state(char *buf, t_fsm_redir *machine)
{
	if (*buf == '"' && !machine->flag_quote)
		machine->state = R_FLAG;
	else if (*buf == '\'' && !machine->flag_dquote)
		machine->state = R_FLAG;
	else if (*buf == '\\' && backslash_activated(buf, machine))
		machine->state = R_BACKSLASH;
	else if ((*buf == '>' || *buf == '<') &&
	!machine->flag_quote && !machine->flag_dquote)
		machine->state = R_FLAG_REDIR;
	else if (*buf == '$' && !machine->flag_quote && ft_is_dollar_start(buf[1]))
		machine->state = R_DOLLAR;
	else if (!machine->flag_quote && !machine->flag_dquote && !machine->flag_redir // les whitespace dans les redir sont gérés a part
	&& (*buf == 9 || *buf == 32))
		machine->state = R_WHITESPACE;
	else
		machine->state = R_LETTER;
}

int				parse_cmd_redir(t_cmd *cmd)
{
	t_fsm_redir			machine;
	static t_func_redir	func[NB_STATE_REDIR] = {red_letter, red_backslash,
	red_flag, red_flag_redir, red_dollar, red_whitespace};
	int					ret;
	char				*buf;
	char				*save;
	
	buf = ft_strdup(cmd->buf); // on initialise buf, que l'on va parser
	save = buf; // on save buf pour pouvoir le free à la fin
	free(cmd->buf); // on free cmd->buf 
	cmd->buf = ft_strdup(""); // on initialise cmd->buf avec une chaine vide (pour ne pas avoir de problème avec les ft_strjoin)
	// on remplira cmd->buf au fur et a mesure du parsing de "buf", avec des ft_strjoin
	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	machine.flag_redir = 0;
	while (*buf != '\0')
	{
		chose_state(buf, &machine);
		ret = func[machine.state](&machine, buf, cmd);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	free(save);
	return (SUCCESS);
}

int			parse_pipe_redir(t_list *pipe_list)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	cmd_list = (t_list*)pipe_list->content;
	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		if (parse_cmd_redir(cmd) == FAILURE)
			return (FAILURE);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

int			parser_redir(t_list *pipe_list)
{
	while (pipe_list)
	{
		if (parse_pipe_redir(pipe_list) == FAILURE)
			return (FAILURE);
		pipe_list = pipe_list->next;
	}
	return (SUCCESS);
}

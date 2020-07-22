/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/07/22 15:49:02 by grim             ###   ########.fr       */
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

int red_flag_redir(t_fsm_redir *m, char *buf, t_cmd *cmd)
{
	int		ret;
	t_redir	*redir;
	
	// init le t_redir suivant de la chaine et set l'int en fonction du signe < > ou >>
	redir = malloc(sizeof(t_redir));
	redir->state = REDIR_OUT; // a modifier
	redir->file = ft_strdup(""); // pour permettre les str_join
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
	if (buf[0] == '>' && buf[1] == '>')
		ret = 2;
	else
		ret = 1;
	while (buf[ret] == 9 || buf[ret] == 32)
		ret++;
	m->flag_redir = 1;
	return (ret);
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
	else
		machine->state = R_LETTER;
}

int				parse_cmd_redir(t_cmd *cmd)
{
	t_fsm_redir			machine;
	static t_func_redir	func[NB_STATE_REDIR] = {red_letter, red_backslash,
	red_flag, red_flag_redir};
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
		if (machine.flag_redir)
			printf("redir activated\n");
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

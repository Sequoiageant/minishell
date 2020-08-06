/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:55:37 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:24:47 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int		backslash_activated(char *buf, t_fsm_cmd *machine)
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

static void		chose_state(char *buf, t_fsm_cmd *machine)
{
	if (*buf == '"' && !machine->flag_quote)
		machine->state = SP_FLAG_DQUOTE;
	else if (*buf == '\'' && !machine->flag_dquote)
		machine->state = SP_FLAG_QUOTE;
	else if (*buf == '\\' && backslash_activated(buf, machine))
		machine->state = SP_BACKSLASH;
	else if ((*buf == '>' || *buf == '<') &&
	!machine->flag_quote && !machine->flag_dquote)
		machine->state = SP_REDIR_ON;
	else if ((*buf == TAB || *buf == SPACE) && machine->flag_redir &&
	!machine->flag_quote && !machine->flag_dquote)
		machine->state = SP_REDIR_OFF;
	else if (*buf == '$' && !machine->flag_quote && ft_is_dollar_start(buf[1]))
		machine->state = SP_DOLLAR;
	else if (!machine->flag_quote && !machine->flag_dquote
	&& !machine->flag_redir && (*buf == TAB || *buf == SPACE))
		machine->state = SP_WHITESPACE;
	else
		machine->state = SP_LETTER;
}

int				parser_split_cmd(t_cmd *cmd)
{
	t_fsm_cmd			machine;
	static t_func_split	func[NB_SPLIT_CMD] = {sp_letter, sp_backslash,
	sp_flag_quote, sp_flag_dquote, sp_flag_redir_on, sp_flag_redir_off,
	sp_whitespace, sp_dollar};
	int					ret;
	char				*buf;
	char				*save;

	buf = ft_strdup(cmd->buf);
	save = buf;
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

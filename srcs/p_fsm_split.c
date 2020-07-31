/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:55:37 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 11:43:57 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	else if ((*buf == '>' || *buf == '<') && // activer le flag
	!machine->flag_quote && !machine->flag_dquote)
		machine->state = SP_REDIR_ON;
	else if ((*buf == TAB || *buf == SPACE) && machine->flag_redir &&// desactiver le flag redir lorsqu'on rencontre un espace ou un tab non "escapés"
	!machine->flag_quote && !machine->flag_dquote)
		machine->state = SP_REDIR_OFF;
	else if (!machine->flag_quote && !machine->flag_dquote && !machine->flag_redir // les whitespace dans les redir sont gérés a part
	&& (*buf == TAB || *buf == SPACE))
		machine->state = SP_WHITESPACE;
	else
		machine->state = SP_LETTER;
}

int				parse_cmd_split(t_cmd *cmd)
{
	t_fsm_cmd			machine;
	static t_func_split	func[NB_STATE_SPLIT] = {sp_letter, sp_backslash,
	sp_flag_quote, sp_flag_dquote, sp_flag_redir_on, sp_flag_redir_off, sp_whitespace};
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
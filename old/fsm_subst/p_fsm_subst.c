/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_subst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:54:48 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 10:19:18 by grim             ###   ########.fr       */
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
		machine->state = SU_FLAG_DQUOTE;
	else if (*buf == '\'' && !machine->flag_dquote)
		machine->state = SU_FLAG_QUOTE;
	else if (*buf == '\\' && backslash_activated(buf, machine))
		machine->state = SU_BACKSLASH;
	else if (*buf == '$' && !machine->flag_quote && ft_is_dollar_start(buf[1]))
		machine->state = SU_SUBST;
	else
		machine->state = SU_LETTER;
}

int				parse_cmd_subst(t_cmd *cmd, t_list *env)
{
	t_fsm_cmd			machine;
	static t_func_subst	func[NB_STATE_SUBST] = {su_letter, su_backslash,
	su_flag_quote, su_flag_dquote, su_subst};
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
	while (*buf != '\0')
	{
		chose_state(buf, &machine);
		ret = func[machine.state](&machine, buf, cmd, env);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	free(save);
	return (SUCCESS);
}
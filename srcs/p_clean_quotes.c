/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_clean_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 12:21:56 by grim              #+#    #+#             */
/*   Updated: 2020/08/03 14:22:23 by grim             ###   ########.fr       */
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
	else
		machine->state = SP_LETTER;
}

int			clean_quotes_str(char **cleaned)
{
	t_fsm_cmd			machine;
	static t_func_clean	func[NB_STATE_CLEAN] = {cl_letter, cl_backslash,
	cl_flag_quote, cl_flag_dquote};
	int					ret;
	char				*buf;
	char				*save;
	
	buf = ft_strdup(*cleaned); // on initialise buf, que l'on va parser
	save = buf; // on save buf pour pouvoir le free à la fin
	free(*cleaned); // on free la string initiale
	*cleaned = ft_strdup(""); // on initialise *cleaned avec une chaine vide (pour ne pas avoir de problème avec les ft_strjoin)
	// on remplira *cleaned au fur et a mesure du parsing de "buf", avec des ft_strjoin
	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	while (*buf != '\0')
	{
		chose_state(buf, &machine);
		ret = func[machine.state](&machine, buf, cleaned);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	free(save);
	return (SUCCESS);
}

int			clean_quotes_cmd(t_cmd *cmd)
{
	char **str;
	int i;

	i = 0;
	while (cmd->argv[i])
	{
		str = (char**)&cmd->argv[i];
		clean_quotes_str(str);
		i++;
	}
	while (cmd->redir)
	{
		str = (char**)&cmd->redir->content;
		clean_quotes_str(str);
		cmd->redir = cmd->redir->next;
	}
	return (SUCCESS);
}

int			clean_quotes(t_list *cmd_list)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = (t_cmd*)cmd_list->content;
		#ifdef DEBUG_PARSING
			printf("\nPARSING CLEAN\n");
		#endif
		if (clean_quotes_cmd(cmd) == FAILURE)
			return (FAILURE);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

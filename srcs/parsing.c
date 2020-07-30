/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/07/30 12:29:01 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

static int	backslash_activated(char *buf, t_state_machine *machine)
{
	if (machine->flag_quote)
		return (0);
	if (machine->flag_dquote)
	{
		if (buf[1] == '$' || buf[1] == '"' || buf[1] == '\\')
			return (TRUE);
		else
			return (FALSE);
	}
	return (1);
}

static void	chose_state(char *buf, t_state_machine *machine)
{
	if (*buf == '"' && !machine->flag_quote)
		machine->state = FLAG;
	else if (*buf == '\'' && !machine->flag_dquote)
		machine->state = FLAG;
	else if (*buf == '\\' && backslash_activated(buf, machine))
		machine->state = BACKSLASH;
	else if (*buf == ';' && !machine->flag_quote && !machine->flag_dquote)
		machine->state = MULTI;
	else if (*buf == '|' && !machine->flag_quote && !machine->flag_dquote)
		machine->state = PIPE;
	else
		machine->state = LETTER;
}

int			parser(char *buf, t_list *env, t_list **pipe_list)
{
	t_state_machine		machine;
	static t_function	func[NB_STATE] = {fsm_letter,
	fsm_backslash, fsm_flag, fsm_multi, fsm_pipe};
	int					ret;

	machine.flag_dquote = 0;
	machine.flag_quote = 0;
	while (*buf != '\0')
	{
		chose_state(buf, &machine);
		ret = func[machine.state](buf, &machine, env, pipe_list);
		if (ret == FAILURE)
			return (FAILURE);
		buf += ret;
	}
	return (SUCCESS);
}

int			ft_parse(char *buf, t_list *env, t_list **pipe_list)
{
	#ifdef DEBUG_PARSING
		printf("LEXER \n");
	#endif
	if (lexer(buf) == FAILURE)
	{
		g_glob.ret = 2;
		ft_putstr_fd("synthax error\n", 2);
		return (FAILURE);
	}
	ft_lstadd_back(pipe_list, ft_lstnew(NULL));
	if (add_cmd(*pipe_list) == FAILURE)
		return (FAILURE);
	#ifdef DEBUG_PARSING
		printf("\n1ST PARSING \n");
	#endif
	if (parser(buf, env, pipe_list) == FAILURE)
		return (FAILURE);
	#ifdef DEBUG_PARSING
		printf("\nPARSING REDIR \n");
	#endif
	if (parser_redir(*pipe_list) == FAILURE)
		return (FAILURE);
	#ifdef DEBUG_PARSING
		print_commands(*pipe_list);
	#endif
	return (EXIT_SUCCESS);
}

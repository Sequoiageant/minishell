/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 11:41:12 by grim             ###   ########.fr       */
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
	static t_function	func[NB_STATE_MULTI] = {fsm_letter,
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

int			split_buf(char *buf, t_list *env, t_list **pipe_list)
{
	#ifdef DEBUG_PARSING
		printf("\n SPLIT BUF\n");
	#endif
	ft_lstadd_back(pipe_list, ft_lstnew(NULL));
	add_cmd(*pipe_list);
	if (parser(buf, env, pipe_list) == FAILURE)
		return (FAILURE);	
	#ifdef DEBUG_PARSING
		printf("\nPrinting pipe_list\n");
		print_pipe_list(*pipe_list);
	#endif
	return (SUCCESS);
}

int			split_cmd(t_list *env, t_list *pipe_list)
{
	t_list *cmd_list;
	
	#ifdef DEBUG_PARSING
		printf("\n SPLIT CMD\n");
	#endif
	while (pipe_list)
	{
		cmd_list = (t_list *)pipe_list->content;
		parsing_cmd(cmd_list, env);
		pipe_list = pipe_list->next;
		#ifdef DEBUG_PARSING
			printf("\nPrinting cmd_list\n");
			print_cmd_list(cmd_list);
		#endif
	}
	return (SUCCESS);
	
}

int			parser_split(char *buf, t_list *env, t_list **pipe_list)
{
	if (split_buf(buf, env, pipe_list) == FAILURE)
		return (FAILURE);
	if (split_cmd(env, *pipe_list) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int			ft_parse(char *buf, t_list *env, t_list **pipe_list)
{
	if (lexer(buf) == FAILURE)
	{
		g_glob.ret = 2;
		ft_putstr_fd("synthax error\n", 2);
		return (FAILURE);
	}
	if (parser_split(buf, env, pipe_list) == FAILURE)
		return (FAILURE);
	return (EXIT_SUCCESS);
}

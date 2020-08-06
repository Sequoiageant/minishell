/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lexer_fsm2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 12:08:29 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:29:08 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static int	rien_avant(char *avant)
{
	int i;

	if (ft_strlen(avant) == 0)
	{
		free(avant);
		return (TRUE);
	}
	i = ft_strlen(avant) - 1;
	while (avant[i] == SPACE || avant[i] == TAB)
		i--;
	if (ft_is_special(avant[i]))
	{
		free(avant);
		return (TRUE);
	}
	free(avant);
	return (FALSE);
}

static int	rien_apres(char *apres)
{
	int i;

	i = 0;
	while (apres[i] == SPACE || apres[i] == TAB)
		i++;
	if (ft_is_special(apres[i]))
	{
		free(apres);
		return (TRUE);
	}
	free(apres);
	return (FALSE);
}

int			lex_check_avant(t_fsm_lexer *m, char *buf, int i)
{
	(void)m;
	if (rien_avant(ft_substr(buf, 0, i)) == TRUE)
		return (FAILURE);
	return (1);
}

int			lex_check_apres(t_fsm_lexer *m, char *buf, int i)
{
	(void)m;
	if (buf[i] == '<')
		if (rien_apres(ft_substr(buf, i + 1, ft_strlen(buf))) == TRUE)
			return (FAILURE);
	if (buf[i] == '>')
	{
		if (buf[i + 1] == '>')
			i++;
		if (rien_apres(ft_substr(buf, i + 1, ft_strlen(buf))) == TRUE)
			return (FAILURE);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fsm_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:55:37 by grim              #+#    #+#             */
/*   Updated: 2020/07/31 11:45:02 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		sp_backslash(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);
}
int		sp_flag_quote(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);

}
int		sp_flag_dquote(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);
	
}
int		sp_flag_redir_on(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);
	
}
int		sp_flag_redir_off(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);
	
}
int		sp_letter(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);
	
}
int		sp_whitespace(t_fsm_cmd *m, char *buf, t_cmd *cmd)
{
    (void)m;
    (void)buf;
    (void)cmd;
    return(1);
	
}
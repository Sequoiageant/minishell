/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/06/24 15:36:12 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H


typedef struct	s_cmd
{
	char		**argv;
	int			argc;
    int         output_file; // >
    int         output_file_append; // >>
    int         input_file; // <
    char        *file; // pour >, >> et <
    int         chained_input; // cmd |
    int         chained_output; // | cmd
}				t_cmd;

int ft_parse(char *buf, t_list *env, t_list **cmd );
int ft_fill_cmd(t_list *cmd_list, char *buf);

#endif
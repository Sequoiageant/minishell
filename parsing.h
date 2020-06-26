/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 09:59:10 by grim              #+#    #+#             */
/*   Updated: 2020/06/26 11:55:54 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H



// etat normal

// etat '
// etat "
// etat backslash

// etat $

// etat ;
// etat |

// echappement oui ou non (en fonction de la combinaison '', "" et backslash)
// si non:
//     etat ;
//     etat |
// si oui: etat normal

// etat substitution oui ou non (en fonction de la combinaison '', "" et backslash)
// si oui:
//     etat $
// si non:
//     etat normal




// buffer = une ou plusieurs pipelines
// pipeline = une ou plusieurs commandes


// cmd 1 ; cmd2 | cmd 3 | cmd4 ; cmd5
// 3 pipeline avec 1 cmd, 3 cmd, 1 cmd


// t_list  *pipeline_list

// pipeline_list->content = (t_pipeline *)pipeline
// pipeline_list->next = autre t_pipeline


// typedef struct	s_pipeline
// {
//     t_list      *cmd;
// }				t_pipeline;

// cmd->content = (t_cmd*)cmd;

// typedef struct s_cmd
// {
//     char		    **argv;
// 	   int		    argc;
//     int         output_file; // >
//     int         output_file_append; // >>
//     int         input_file; // <
//     char        *file; // pour >, >> et <
// }               t_cmd;



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
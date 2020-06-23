/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:42 by grim              #+#    #+#             */
/*   Updated: 2020/06/23 12:22:55 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SUBSTITUTION
to do: detecter les caracteres et faire la substitution directement
	$               changer en la variable d'env correspondate, avec un getenv
	''              message affiché tel quel (pas de subsitution)
	""              message analysé pour detecter la présence de $ (et d'échappement (\) ?)

MULTI COMMANDES
to do: alloc plusieurs char **cmd
	;               multi commandes

REDIRECTION
to do: detecter les caracteres et set des flags de redirection
flags de redirection  = infos necessaires pour lancer les syscall "pipe" et/ou "dup"
	>               OUTPUT = file
	>>              OUTPUT = file
	<               INPUT = file on STDIN
	cmd1 | cmd2     OUTPUT of cmd1 is INPUT of cmd 2
cf. sur les pipes et dup: https://tldp.org/LDP/lpg/node10.html#SECTION00721000000000000000
cf. dup_test.c et pipe_test.c
*/

#include "libft.h"
#include "mshell.h"

// ft_parse(char *buf)
// {

// }
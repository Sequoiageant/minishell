/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:53:25 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 19:53:37 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void    ft_print_status(int status)
{
	if (WIFEXITED(status)) {
		printf("terminé, code=%d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("tué par le signal %d\n", WTERMSIG(status));
	} else if (WIFSTOPPED(status)) {
		printf("arrêté par le signal %d\n", WSTOPSIG(status));
	} else if (WIFCONTINUED(status)) {
		printf("relancé\n");
	}
}
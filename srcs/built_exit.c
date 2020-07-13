/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:27:32 by julnolle          #+#    #+#             */
/*   Updated: 2020/07/11 16:30:05 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ms_exit(t_list *cmd_list, t_list **env)
{
	ft_lstclear(&cmd_list, &del_cmd);
	ft_lstclear(env, &del_key_val);
	ft_putendl_fd("La fonction doit tout free, vérifier que ce soit le cas", 2);
	exit(SUCCESS);
}

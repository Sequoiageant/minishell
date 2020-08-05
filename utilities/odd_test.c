/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:20:40 by julnolle          #+#    #+#             */
/*   Updated: 2020/08/04 12:24:04 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		is_odd(int nb)
{
	return ((nb % 2) != 0);
}

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		if (is_odd(atoi(argv[1])))
			printf("%s: odd\n", argv[1]);
		else
			printf("%s: even\n", argv[1]);
	}
	return (0);
}
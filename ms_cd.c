/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/06/23 14:49:43 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// https://man7.org/linux/man-pages/man1/cd.1p.html
// pas d'argument à gérer puisque -L et -P ne servent qu'à gerer ou non des cd vers des liens symboliques
 // TO DO:
	// pas le droit à getenv ??
	// 1) gerer le cas ou cdvars est activé (doit remplacer l'argument par sa valeur si celui ci est une variable)
	// 2) gerer la recherche dans cdpath
	//      Attention: printer le cwd une fois trouvé
	// 3) changer la valeur de PWD et de OLD_PWD
	//      Remarque: après un chdir, $PATH reste inchangé (En revanche, getcwd() renvoie bien le nouveau cwd) -> il faut donc le changer "à la main"
	// 4) coder ft_strcmp et l'ajouter à la libft. Puis remplacer strcmp par ft_strcmp ci dessous
	// 5) gerer le "cd -": go back to OLD_PWD
	//      Attention: printer le cwd une fois trouvé


void ft_cd_change_env(t_list **env)
{
	(void)env;
}

void	ft_cd_perror(char **argv)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
}

int		ms_cd(int argc, char **argv, t_list **env)
{
	int	ret;

	if (argc == 1)
	{
		if (getenv("HOME") == NULL || strcmp(getenv("HOME"), "") == 0)
			return (1);
		ret = chdir(getenv("HOME"));
	}
	if (argc > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		return (1);
	}
	if (argc == 2)
		ret = chdir(argv[1]);
	if (ret)
		ft_cd_perror(argv);
	else
		ft_cd_change_env(env);
	return (ret);
}
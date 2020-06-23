/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/06/23 16:22:30 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// https://man7.org/linux/man-pages/man1/cd.1p.html
// pas d'argument à gérer puisque -L et -P ne servent qu'à gerer ou non des cd vers des liens symboliques
 // TO DO:
	// 1) gerer le cas ou cdvars est activé (doit remplacer l'argument par sa valeur si celui ci est une variable)
	// 2) gerer la recherche dans cdpath
	//      Attention: printer le cwd une fois trouvé
	// 3) changer la valeur de PWD et de OLD_PWD = OK fait mais utiliser set dans le cas ou PWD/OLDPWD n'est pas set (plutot que de le faire à la main)
	//      Remarque: après un chdir, $PATH reste inchangé (En revanche, getcwd() renvoie bien le nouveau cwd) -> il faut donc le changer "à la main"
	// 4) gerer le "cd -": go back to OLD_PWD
	//      Attention: printer le cwd une fois trouvé


void ft_cd_change_env(t_list **env, char *oldpwd)
{
	t_key_val *env_pwd;
	t_key_val *env_oldpwd;
	if ((env_oldpwd = find_key_val(*env, "OLDPWD")) == NULL) //cas où OLDPWD n'est pas set
	{
		env_oldpwd = malloc(sizeof(t_key_val));
		env_oldpwd->key = ft_strdup("OLDPWD");
		ft_lstadd_back(env, ft_lstnew(env_oldpwd));
	}
	else
		free(env_oldpwd->val);
	env_oldpwd->val = oldpwd;
	
	if ((env_pwd = find_key_val(*env, "PWD")) == NULL) //cas ou PWD n'est pas set
	{
		env_pwd = malloc(sizeof(t_key_val));
		env_pwd->key = ft_strdup("PWD");
		ft_lstadd_back(env, ft_lstnew(env_pwd));
	}
	else
		free(env_pwd->val);
	env_pwd->val = getcwd(NULL, 0);
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
	int		ret;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (argc == 1)
	{
		if (getenv("HOME") == NULL || ft_strcmp(getenv("HOME"), "") == 0)
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
		ft_cd_change_env(env, old_pwd);
	print_env_elem(*env, "PWD");
	print_env_elem(*env, "OLDPWD");
	return (ret);
}
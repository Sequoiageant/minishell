/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/08/04 16:12:38 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

// https://man7.org/linux/man-pages/man1/cd.1p.html
// pas d'argument à gérer puisque -L et -P ne servent qu'à gerer ou non des cd vers des liens symboliques
// pas à gérer le cd - (back to OLD_PWD) puisque ca n'est pas un chemin relatif ou absolu ?
// pas gerer le cas ou cdvars est activé car cette option ne semble pas dispo dans bash
// 		(doit remplacer l'argument par sa valeur si celui ci est une variable)
 // TO DO:
	// 1) gerer la recherche dans cdpath
	//      Attention: printer le cwd une fois trouvé
	//		Attention: cherche dans cdpath avant de chercher dans le current dir


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
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

int		handle_cd(char *dir, t_list *env)
{
	t_key_val	*key;

	if (ft_strcmp(dir, "-") == 0)
		return (cd_back_to_oldpwd(env));
	// if ((key = find_key_val(env, "CDPATH"))) // si CD PATH est set
	// {
	// 	(void)dir;
	// 	(void)env;
	// 	// cheche "dir" dans chaque element du CDPATH
	// 	// si ne trouve pas, va à ./dir
	// }
	return (chdir(dir));
}

int		ms_cd(int argc, char **argv, t_list **env)
{
	int			ret;
	char		*old_pwd;
	t_key_val	*key;

	old_pwd = getcwd(NULL, 0);
	if (argc > 2)
		return (cd_too_many_args(old_pwd));
	if (argc == 1)
	{
		if ((key = find_key_val(*env, "HOME")) == NULL || !ft_strcmp(key->val, ""))
			return (cd_home_not_set(key, old_pwd));
		ret = chdir(key->val);
	}
	if (argc == 2)
		ret = handle_cd(argv[1], *env);
	if (ret == FAILURE)
	{
		if (!(argc == 2 && ft_strcmp(argv[1], "-") == 0)) // dans le cas ou le probleme est lié à un cd -, on affiche pas le message d'erreur classique
			ft_cd_perror(argv);
		free(old_pwd);
		return (FAILURE);
	}
	ft_cd_change_env(env, old_pwd);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:30 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/11 14:52:40 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static void	ft_cd_change_env(t_list **env, char *dir, t_key_val *env_pwd)
{
	t_key_val	*env_oldpwd;
	char		*old_pwd;
	char		*tmp;

	old_pwd = ft_strdup(env_pwd->val);
	if ((tmp = getcwd(NULL, 0)))
	{
		free(env_pwd->val);
		env_pwd->val = tmp;
	}
	else
	{
		ft_strjoin_back("/", &env_pwd->val);
		ft_strjoin_back(dir, &env_pwd->val);
	}
	if ((env_oldpwd = find_key_val(*env, "OLDPWD")))
	{
		free(env_oldpwd->val);
		env_oldpwd->val = old_pwd;
	}
	else
		free(old_pwd);
}

int			change_env(int argc, t_list **env, char **argv, t_key_val *key)
{
	t_key_val *env_pwd;

	if ((env_pwd = find_key_val(*env, "PWD")))
	{
		if (argc == 2)
			ft_cd_change_env(env, argv[1], env_pwd);
		else
			ft_cd_change_env(env, key->val, env_pwd);
	}
	return (SUCCESS);
}

static void	ft_cd_perror(char **argv)
{
	ft_putstr_fd("bash: cd: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

static int	handle_cd(char *dir, t_list *env)
{
	char		*cdpath_dir;
	int			ret;
	char		*tmp;

	if (ft_strcmp(dir, "-") == 0)
		return (cd_back_to_oldpwd(env));
	cdpath_dir = NULL;
	if (ft_strcmp(dir, "..") != 0 && ft_strcmp(dir, ".") != 0)
		cdpath_dir = cd_find_path(env, dir);
	if (cdpath_dir)
	{
		ret = chdir(cdpath_dir);
		if ((tmp = getcwd(NULL, 0)))
		{
			ft_putendl_fd(tmp, 1);
			free(tmp);
		}
		free(cdpath_dir);
		return (ret);
	}
	return (chdir(dir));
}

int			ms_cd(int argc, char **argv, t_list **env)
{
	int			ret;
	char		*tmp;
	t_key_val	*key;

	if (argc > 2)
		return (cd_too_many_args());
	if (argc == 1)
	{
		if ((key = find_key_val(*env, "HOME")) == NULL
			|| !ft_strcmp(key->val, ""))
			return (cd_home_not_set(key));
		ret = chdir(key->val);
	}
	if (argc == 2)
		ret = handle_cd(argv[1], *env);
	if (ret == FAILURE)
	{
		if (!(argc == 2 && ft_strcmp(argv[1], "-") == 0))
			ft_cd_perror(argv);
		return (FAILURE);
	}
	if ((tmp = getcwd(NULL, 0)) == NULL)
		ft_putendl_fd(strerror(errno), 2);
	free(tmp);
	return (change_env(argc, env, argv, key));
}

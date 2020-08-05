/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:30 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 20:20:22 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	ft_cd_change_env(t_list **env, char *oldpwd)
{
	t_key_val *env_pwd;
	t_key_val *env_oldpwd;

	if ((env_oldpwd = find_key_val(*env, "OLDPWD")) == NULL)
	{
		env_oldpwd = malloc(sizeof(t_key_val));
		env_oldpwd->key = ft_strdup("OLDPWD");
		ft_lstadd_back(env, ft_lstnew(env_oldpwd));
	}
	else
		free(env_oldpwd->val);
	env_oldpwd->val = oldpwd;
	if ((env_pwd = find_key_val(*env, "PWD")) == NULL)
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
	if (ft_strcmp(dir, "-") == 0)
		return (cd_back_to_oldpwd(env));
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
		if ((key = find_key_val(*env, "HOME")) == NULL
			|| !ft_strcmp(key->val, ""))
			return (cd_home_not_set(key, old_pwd));
		ret = chdir(key->val);
	}
	if (argc == 2)
		ret = handle_cd(argv[1], *env);
	if (ret == FAILURE)
	{
		if (!(argc == 2 && ft_strcmp(argv[1], "-") == 0))
			ft_cd_perror(argv);
		free(old_pwd);
		return (FAILURE);
	}
	ft_cd_change_env(env, old_pwd);
	return (SUCCESS);
}

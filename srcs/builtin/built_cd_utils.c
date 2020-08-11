/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:12:14 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/11 14:52:19 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

int		cd_home_not_set(t_key_val *key)
{
	if (key)
		return (SUCCESS);
	else
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (FAILURE);
	}
}

int		cd_too_many_args(void)
{
	ft_putstr_fd("bash: cd: too many arguments\n", 2);
	return (FAILURE);
}

int		cd_back_to_oldpwd(t_list *env)
{
	t_key_val *oldpwd;

	if ((oldpwd = find_key_val(env, "OLDPWD")) == NULL)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		return (FAILURE);
	}
	else
	{
		ft_putendl_fd(oldpwd->val, 1);
		return (chdir(oldpwd->val));
	}
}

char	*add_slash(char *path)
{
	char *modified;

	if (path[ft_strlen(path) - 1] == '/')
		modified = ft_strdup(path);
	else
		modified = ft_strjoin(path, "/");
	return (modified);
}

char	*cd_find_path(t_list *env, char *cmd)
{
	size_t	i;
	DIR		*dir;
	char	**path;
	char	*selected_path;

	if ((path = ft_split(find_env_val(env, "CDPATH"), ':')))
	{
		i = 0;
		while (path[i])
		{
			selected_path = add_slash(path[i]);
			ft_strjoin_back(cmd, &selected_path);
			if ((dir = opendir(selected_path)))
			{
				free_tab2(path);
				closedir(dir);
				return (selected_path);
			}
			free(selected_path);
			i++;
		}
		free_tab2(path);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_filler_cmdpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:09:47 by grim              #+#    #+#             */
/*   Updated: 2020/07/09 11:42:12 by grim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

int		ft_ckeck_bin(DIR *dir, char *cmd)
{
	struct dirent	*dir_content;

	while ((dir_content = readdir(dir)))
	{
		if (ft_strcmp(dir_content->d_name, cmd) == 0)
		{
			// printf("Cmd found: %s\n", dir_content->d_name);
			closedir(dir);
			return (TRUE);
		}
	}
	return (FALSE);
}

char	*find_in_env_path(t_list *env, char *cmd)
{
	DIR		*dir;
	size_t	i;
	char	**path;
	char	*selected_path;

	path = ft_split(find_key_val(env, "PATH")->val, ':');
	i = 0;
	while(path[i])
	{
		dir = opendir(path[i]);
		if (dir)
		{
			if (ft_ckeck_bin(dir, cmd) == TRUE)
			{
				selected_path = ft_strjoin(path[i], "/");
				free_tab2(path);
				return (selected_path);
			}
			i++;
			closedir(dir);
		}
	}
	free_tab2(path);
	return (NULL);
}

int	fill_cmd_path(t_cmd *cmd, t_list *env)
{
	cmd->cmd_path = find_in_env_path(env,cmd->argv[0]);
	if (cmd->cmd_path == NULL)
		cmd->cmd_path = ft_strdup(cmd->argv[0]);
	else
		ft_strjoin_back(cmd->argv[0], &(cmd->cmd_path));
	return (SUCCESS);
}
	
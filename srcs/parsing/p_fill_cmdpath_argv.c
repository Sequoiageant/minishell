/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fill_cmdpath_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:09:47 by bbrunet           #+#    #+#             */
/*   Updated: 2020/08/10 15:37:15 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

static char	*ft_ckeck_bin(DIR *dir, char *cmd, char *path)
{
	struct dirent	*dir_content;
	char			*selected_path;

	while ((dir_content = readdir(dir)))
	{
		if (ft_strcmp(dir_content->d_name, cmd) == 0)
		{
			if (path[ft_strlen(path) - 1] == '/')
				selected_path = ft_strdup(path);
			else
				selected_path = ft_strjoin(path, "/");
			closedir(dir);
			return (selected_path);
		}
	}
	return (NULL);
}

char		*find_in_path(t_list *env, char *cmd)
{
	DIR		*dir;
	size_t	i;
	char	**path;
	char	*selected_path;

	if ((path = ft_split(find_env_val(env, "PATH"), ':')))
	{
		i = 0;
		while (path[i])
		{
			if ((dir = opendir(path[i])))
			{
				if ((selected_path = ft_ckeck_bin(dir, cmd, path[i])))
				{
					free_tab2(path);
					return (selected_path);
				}
				closedir(dir);
			}
			i++;
		}
		free_tab2(path);
	}
	return (NULL);
}

static int	fill_cmd_path(t_cmd *cmd, t_list *env)
{
	if (ft_strcmp(cmd->argv[0], ".") && ft_strcmp(cmd->argv[0], ".."))
		cmd->cmd_path = find_in_path(env, cmd->argv[0]);
	else
		cmd->cmd_path = NULL;
	if (cmd->cmd_path == NULL)
	{
		if (ft_strchr(cmd->argv[0], '/') != NULL)
			cmd->cmd_path = ft_strdup(cmd->argv[0]);
	}
	else
		ft_strjoin_back(cmd->argv[0], &(cmd->cmd_path));
	return (SUCCESS);
}

int			fill_cmdlist_path(t_list *cmd_list, t_list *env)
{
	t_cmd *cmd;

	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (cmd->argv[0])
			fill_cmd_path(cmd, env);
		cmd_list = cmd_list->next;
	}
	return (SUCCESS);
}

char		**ft_list_to_tab_argv(t_list *argv)
{
	char		**argv_tab;
	int			size;
	int			i;

	size = ft_lstsize(argv);
	argv_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (argv_tab)
	{
		argv_tab[size] = NULL;
		i = 0;
		while (argv)
		{
			argv_tab[i] = ft_strdup((char *)(argv->content));
			argv = argv->next;
			i++;
		}
	}
	return (argv_tab);
}

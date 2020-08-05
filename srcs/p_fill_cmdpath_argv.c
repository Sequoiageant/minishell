/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fill_cmdpath_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grim <grim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 11:09:47 by grim              #+#    #+#             */
/*   Updated: 2020/08/05 18:30:42 by grim             ###   ########.fr       */
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

	if ((path = ft_split(find_env_val(env, "PATH"), ':')))
	{
		i = 0;
		while (path[i])
		{
			if ((dir = opendir(path[i])))
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
	}
	return (NULL);
}

int		fill_cmd_path(t_cmd *cmd, t_list *env)
{
	cmd->cmd_path = find_in_env_path(env, cmd->argv[0]);
	if (cmd->cmd_path == NULL)
	{
		if (ft_strchr(cmd->argv[0], '/') != NULL)
			cmd->cmd_path = ft_strdup(cmd->argv[0]);
	}
	else
		ft_strjoin_back(cmd->argv[0], &(cmd->cmd_path));
	return (SUCCESS);
}

int		fill_cmdlist_path(t_list *cmd_list, t_list *env)
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

int		fill_argv(t_cmd *cmd)
{
	int i;

	cmd->argv = ft_split(cmd->buf, ' ');
	if (cmd->argv == NULL)
		return (FAILURE);
	i = 0;
	while (cmd->argv[i])
		i++;
	cmd->argc = i;
	return (SUCCESS);
}

char	**ft_list_to_tab_argv(t_list *argv)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:09 by grim              #+#    #+#             */
/*   Updated: 2020/07/02 18:29:04 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	free_tab2(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

char		**ft_list_to_tab(t_list *env)
{
	char		**env_tab;
	t_key_val	*elem;
	int			size;
	int			i;

	size = ft_lstsize(env);
	env_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (env_tab)
	{
		env_tab[size] = NULL;
		i = 0;
		while (env)
		{
			elem = (t_key_val *)(env->content);
			env_tab[i] = ft_calloc(ft_strlen(elem->key) + ft_strlen(elem->val) + 2, 1);
			ft_strcat(env_tab[i], elem->key);
			ft_strcat(env_tab[i], "=");
			ft_strcat(env_tab[i], elem->val);
			env = env->next;
			i++;
		}
	}
	return (env_tab);
}

int		ft_ckeck_bin(DIR *dir, char *cmd)
{
	struct dirent	*dir_content;

	while ((dir_content = readdir(dir)))
	{
		if (ft_strcmp(dir_content->d_name, cmd) == 0)
		{
			printf("Cmd found: %s\n", dir_content->d_name);
			return (TRUE);
		}
	}
	return (FALSE);
}

char	*ft_is_in_path(t_list *env, char *cmd)
{
	DIR		*dir;
	size_t	i;
	char	*path;
	char	**paths;

	path = find_key_val(env, "PATH")->val;
	paths = ft_split(path, ':');
	i = 0;
	while(paths[i])
	{
		dir = opendir(paths[i]);
		if (ft_ckeck_bin(dir, cmd) == TRUE)
		{
			ft_strjoin_back("/", &paths[i]);
			return (paths[i]);
		}
		i++;
	}
	return (NULL);
}

int		ft_fork(char **cmd, t_list **env)
{
	int		status;
	char	*filepath;
	char	**env_tab;
	
	env_tab = ft_list_to_tab(*env);
	if ((filepath = ft_is_in_path(*env, cmd[0])))
	{
		new_pid = fork();
		if (new_pid == 0)
		{
		// new process
		// ft_putstr_fd(">>Inside new process\n", 1);
		// va chercher ./cmd[0] pour l'executer
		// il faudrait au préalable chercher dans PATH pour trouver l'executable correspondant à la commande. Puis donner le "chemin" de cet executable en input (à la place de cmd[0])
		// ft_strlcat(filepath, "executables/", 100);
			ft_strjoin_back(cmd[0], &filepath);
			printf("filename: %s\n", filepath);
			if (execve(filepath, cmd, env_tab) == -1)
				printf(">>Exec failed\n");
			free_tab2(env_tab);
		// else should not return
		}
		else
		{
		// old process
			waitpid(new_pid, &status, 0);
		// return (new_pid);
		}
	}
	else
		ft_putendl_fd("Command not found", 1);
	free(filepath);
	return (0);
}

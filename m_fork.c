/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_fork.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:15:09 by grim              #+#    #+#             */
/*   Updated: 2020/07/04 12:41:11 by julnolle         ###   ########.fr       */
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

void	display_tab2(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
	{
		ft_putendl_fd(tab[i], 1);
		i++;
	}
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

char	*find_in_env_path(t_list *env, char *cmd)
{
	DIR		*dir;
	size_t	i;
	char	*path;
	char	**paths;

	path = find_key_val(env, "PATH")->val;
	paths = ft_split(path, ':');
	// display_tab2(paths);
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
	filepath = find_in_env_path(*env, cmd[0]);
	if (filepath == NULL)
	{
		free(filepath);
		filepath = ft_strdup(cmd[0]);
	}
	else
		ft_strjoin_back(cmd[0], &filepath);
	new_pid = fork();
	if (new_pid == 0)
	{
		printf("filename: %s\n", filepath);
		if (execve(filepath, cmd, env_tab) == -1)
			ft_putendl_fd("Command not found", 2);
	}
	else
	{
		waitpid(new_pid, &status, 0);
		// Le code qui suit vient du man wait2, à visée de debug plutot
		if (WIFEXITED(status)) {
			printf("terminé, code=%d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("tué par le signal %d\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("arrêté par le signal %d\n", WSTOPSIG(status));
		} else if (WIFCONTINUED(status)) {
			printf("relancé\n");
		}
		new_pid = 0;
		// return (new_pid);
	}
	free_tab2(env_tab); // a mettre en bas je pense, sinon ne sera pas exec
	free(filepath);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_del.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:35:55 by grim              #+#    #+#             */
/*   Updated: 2020/07/29 14:34:47 by julnolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mshell.h"

void	free_tab2(char **tab)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_tab2_stop(char **tab, size_t stop)
{
	size_t i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < stop)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}


void	free_tab2_int(int **tab, int num)
{
	int i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i < num)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	del_key_val(void *elem)
{
	t_key_val *key_val;

	key_val = (t_key_val*)elem;
	free(key_val->key);
	key_val->key = NULL;
	free(key_val->val);
	key_val->val = NULL;
	free(key_val);
	key_val = NULL;
}

void	del_redir(void *elem)
{
	t_redir	*redir;

	redir = (t_redir *)elem;
	free(redir->file);
	redir->file = NULL;
	free(redir);
}

void	del_flag(void *elem)
{
	int	*flag;

	flag = (int*)elem;
	free(flag);
	flag = NULL;
}

void	del_only_t_list(void *elem)
{
	(void)elem;
}

void	del_argv_list_elem(void *elem)
{
	char	*str;

	str = (char*)elem;
	free(str);
	str = NULL;
}

void	del_env_node(t_list **env)
{
	del_key_val((*env)->content);
	free(*env);
	*env = NULL;
}


void	del_argv_node(t_list **argv)
{
	free(*argv);
	*argv = NULL;
}


void    del_cmd(void *elem)
{
    t_cmd	*cmd;

    cmd = (t_cmd*)elem;
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
    	cmd->cmd_path = NULL;
	}
	free(cmd->buf);
   	cmd->buf = NULL;
	ft_lstclear(&cmd->redir, &del_redir);
	ft_lstclear(&cmd->flag, &del_flag);
	ft_lstclear(&cmd->flag_redir, &del_flag);
	free_tab2(cmd->argv);
	ft_lstclear(&cmd->argv_list, &del_only_t_list); // on free juste les t_list pour chaque maillon (les t_list->content ont déja été free par le free_tab2)
	// ft_lstclear(&cmd->argv_list, &del_argv_list_elem);
	// free(cmd->argv); // pas la peine de free les cmd->argv[i]: cmd->argv[i] = content des cmd->argv_list = free au dessus
	free(cmd);
	cmd = NULL;
}

void	del_pipe(void *elem)
{
	t_list *cmd_list;

	cmd_list = (t_list*)elem;
	ft_lstclear(&cmd_list, &del_cmd);
}

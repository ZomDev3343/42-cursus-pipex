/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:36:33 by truello           #+#    #+#             */
/*   Updated: 2024/01/11 13:07:50 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_file(char *cmd_name, char *path)
{
	char	**paths;
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = -1;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		tmp = ft_strnewjoin(paths[i], "/");
		cmd_path = ft_strnewjoin(tmp, cmd_name);
		free(tmp);
		if (access(cmd_path, 0) == 0)
			return (free_parts(paths), cmd_path);
		free(cmd_path);
	}
	return (free_parts(paths), NULL);
}

void	free_cmds(t_cmds *cmds)
{
	if (cmds == NULL)
		return ;
	if (cmds->next)
		free_cmds(cmds->next);
	if (cmds->cmd_file)
		free(cmds->cmd_file);
	if (cmds->cmd_args)
		free_parts(cmds->cmd_args);
	free(cmds);
	cmds = NULL;
}

t_cmds	*newcmd(char *cmd_file, char **cmd_args)
{
	t_cmds	*res;

	res = (t_cmds *) malloc(sizeof(t_cmds));
	if (res == 0)
		return (NULL);
	res->cmd_file = cmd_file;
	res->cmd_args = cmd_args;
	res->next = NULL;
	return (res);
}

void	pbcmd(t_cmds **parent, t_cmds *child)
{
	t_cmds	*tmp;

	tmp = *parent;
	if (tmp == NULL)
		return (*parent = child, (void) 0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = child;
}

int	get_commands(int ac, char **av, char *path, t_cmds **cmds)
{
	int		i;
	char	**args;
	char	*cmd_file;

	i = 1;
	while (++i < ac - 1)
	{
		ft_printf("nfwekggowhgw\n");
		if (!av[i][0])
			return (pbcmd(cmds, newcmd(ft_calloc(1, 1), NULL)), 1);
		args = ft_split(av[i], ' ');
		cmd_file = get_cmd_file(args[0], path);
		ft_printf("CMD FILE : %s\n", cmd_file);
		if (cmd_file == NULL)
			return (free_cmds(*cmds), 0);
		pbcmd(cmds, newcmd(cmd_file, args));
	}
	return (1);
}

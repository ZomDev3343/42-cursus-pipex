/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:36:56 by truello           #+#    #+#             */
/*   Updated: 2024/01/10 16:33:17 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmds_amt(t_cmds *cmds)
{
	int	res;

	res = 0;
	while (cmds)
	{
		res++;
		cmds = cmds->next;
	}
	return (res);
}

int	choose_pipex_mode(char **av, int ac, char **env, t_cmds **cmds)
{
	int	fd;
	int	here_doc_mode;

	here_doc_mode = ft_strcmp(av[1], "here_doc");
	if (here_doc_mode)
		here_doc(av[2], av[ac - 1], *cmds, get_cmds_amt(*cmds));
	if (access(av[1], 0) && get_commands(ac, av, get_path(env), cmds))
		pipex_bonus(av[1], av[ac - 1], *cmds, get_cmds_amt(*cmds));
	else
	{
		unlink(av[ac - 1]);
		fd = open(av[ac - 1], O_CREAT, 0644);
		if (fd == -1)
			return (perror(""), 1);
		close(fd);
	}
	if (*cmds)
		free_cmds(*cmds);
	return (0);
}

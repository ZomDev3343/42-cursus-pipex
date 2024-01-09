/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:36:56 by truello           #+#    #+#             */
/*   Updated: 2024/01/09 13:44:22 by truello          ###   ########.fr       */
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

int	init_pipes_and_pids(int pipe_fd[2][2], int **pids, int amt)
{
	if (pipe(pipe_fd[0]) == -1 || pipe(pipe_fd[1]) == -1)
		return (ft_printf("Pipe error!\n"));
	*pids = (int *) ft_calloc(amt, sizeof(int));
	if (pids == NULL)
		return (ft_printf("Malloc error for pids array!\n"));
	return (1);
}

void	close_pipes(int pipe[2][2])
{
	close(pipe[0][0]);
	close(pipe[0][1]);
	close(pipe[1][0]);
	close(pipe[1][1]);
}

void	wait_all_pids(int *pids, int len)
{
	while (len-- > 0)
		wait(NULL);
}

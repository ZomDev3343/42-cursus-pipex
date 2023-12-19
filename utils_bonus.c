/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:36:56 by truello           #+#    #+#             */
/*   Updated: 2023/12/19 16:27:33 by truello          ###   ########.fr       */
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

int	init_pipes(int **buffer, int amount)
{
	int	i;

	i = -1;
	buffer = (int **) ft_calloc(amount + 1, sizeof(int *));
	if (buffer == NULL)
		return (0);
	while (++i < amount)
	{
		buffer[i] = ft_calloc(2, sizeof(int));
		if (buffer[i] == NULL)
			return (free_pipes(buffer, i + 1), 0);
	}
	while (--i >= 0)
		if (pipe(buffer[i]) == -1)
			return (free_pipes(buffer, amount + 1), 0);
	return (1);
}

void	close_pipes(int **pipes)
{
	int	i;

	i = -1;
	while (pipes[++i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	free_pipes(int **pipes, int amt)
{
	int	i;

	i = -1;
	while (pipes[++i])
		free(pipes[i]);
	free(pipes);
	pipes = NULL;
}

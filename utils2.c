/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:42:33 by tohma             #+#    #+#             */
/*   Updated: 2024/02/26 17:01:31 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_only_command(char *input_file, char *output_file, t_cmds *cmd)
{
	int	r_fd;
	int	w_fd;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		r_fd = open(input_file, O_RDONLY);
		if (r_fd == -1)
			return ;
		w_fd = open(output_file, O_CREAT | O_WRONLY, 0644);
		if (w_fd == -1)
			return ;
		dup2(r_fd, STDIN_FILENO);
		dup2(w_fd, STDOUT_FILENO);
		close(r_fd);
		close(w_fd);
		if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
			perror("");
	}
	return (wait(NULL), (void) 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:36:08 by truello           #+#    #+#             */
/*   Updated: 2024/01/10 16:38:06 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_last_hd(char *output_file, t_cmds *cmd)
{
	int	file_fd;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (perror(""), (void) 0);
	pid = fork();
	if (pid == 0)
	{
		unlink(output_file);
		file_fd = open(output_file, O_CREAT | O_APPEND, 0644);
		if (file_fd == -1)
			return (perror(""));
		dup2(file_fd, STDOUT_FILENO);
		if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
			perror("");
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
}

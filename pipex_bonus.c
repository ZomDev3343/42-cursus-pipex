/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:51:51 by truello           #+#    #+#             */
/*   Updated: 2024/02/26 17:02:52 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first(char *input_file, t_cmds *cmd)
{
	int	file_fd;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (perror(""), (void) 0);
	pid = fork();
	if (pid == 0)
	{
		file_fd = open(input_file, O_RDONLY);
		if (file_fd == -1)
			return (perror(""));
		dup2(file_fd, STDIN_FILENO);
		if (cmd->next)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
			perror("");
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		wait(NULL);
	}
}

void	handle_command(t_cmds *cmd)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (perror(""), (void) 0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
			perror("");
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	handle_last(char *output_file, t_cmds *cmd, int write_mode)
{
	int	file_fd;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (perror(""), (void) 0);
	pid = fork();
	if (pid == 0)
	{
		file_fd = open(output_file, O_CREAT | O_WRONLY | write_mode, 0644);
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

void	pipex_bonus(char *input_file, char *output_file, t_cmds *cmds,
	int cmd_amt)
{
	int	cur_pid;

	cur_pid = 0;
	unlink(output_file);
	if (cmd_amt == 1)
		return (handle_only_command(input_file, output_file, cmds));
	handle_first(input_file, cmds);
	cmds = cmds->next;
	while (++cur_pid < cmd_amt - 1)
	{
		handle_command(cmds);
		cmds = cmds->next;
	}
	handle_last(output_file, cmds, O_WRONLY);
}

int	main(int ac, char **av, char **env)
{
	t_cmds	*cmds;

	if (ac < 4)
		ft_printf("Usage : ./pipex input cmd1 ... cmdn output\n");
	else
		return (cmds = NULL,
			choose_pipex_mode(av, ac, env, &cmds), free_cmds(cmds), 0);
	return (0);
}

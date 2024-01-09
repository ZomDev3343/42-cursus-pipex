/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:51:51 by truello           #+#    #+#             */
/*   Updated: 2024/01/09 14:47:44 by truello          ###   ########.fr       */
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

/*
	Reading pipe id : cur_pid % 2 == 0
	Writing pipe id : cur_pid % 2 != 0
*/
static void	handle_command(t_cmds *cmd)
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

static void	handle_last(char *output_file, t_cmds *cmd)
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
		file_fd = open(output_file, O_CREAT | O_WRONLY, 0644);
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

static void	pipex(char *input_file, char *output_file, t_cmds *cmds,
	int cmd_amt)
{
	int	cur_pid;

	cur_pid = 0;
	handle_first(input_file, cmds);
	cmds = cmds->next;
	while (++cur_pid < cmd_amt - 1)
	{
		handle_command(cmds);
		cmds = cmds->next;
	}
	handle_last(output_file, cmds);
}

int	main(int ac, char **av, char **env)
{
	int		fd;
	t_cmds	*cmds;

	if (ac < 5)
		ft_printf("Usage : ./pipex input cmd1 ... cmdn output\n");
	else
	{
		if (!access(av[1], 0))
		{
			cmds = NULL;
			if (get_commands(ac, av, get_path(env), &cmds))
				return (pipex(av[1], av[ac - 1], cmds, get_cmds_amt(cmds)),
					free_cmds(cmds), 0);
			else
			{
				unlink(av[ac - 1]);
				fd = open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
				close(fd);
			}
		}
		else
			perror(av[1]);
	}
	return (0);
}

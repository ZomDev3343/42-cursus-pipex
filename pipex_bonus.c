/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:51:51 by truello           #+#    #+#             */
/*   Updated: 2024/01/09 14:23:10 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first(char *input_file, t_cmds *cmd, int pipe_fd[2][2])
{
	int	file_fd;

	file_fd = open(input_file, O_RDONLY);
	if (file_fd == -1)
		return (perror(""));
	dup2(file_fd, STDIN_FILENO);
	dup2(pipe_fd[0][1], STDOUT_FILENO);
	close_pipes(pipe_fd);
	close(file_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");

}

/*
	Reading pipe id : cur_pid % 2 == 0
	Writing pipe id : cur_pid % 2 != 0
*/
static void	handle_command(int pipe_fd[2][2], t_cmds *cmd, int cur_pid)
{
	ft_printf("Command name : %s\nArgs : %s\n", cmd->cmd_args[0], cmd->cmd_args[1]);
	dup2(pipe_fd[cur_pid % 2][1], STDOUT_FILENO);
	close_pipes(pipe_fd);
	ft_printf("%d ; %d\n", pipe_fd[cur_pid % 2 == 0][0], pipe_fd[cur_pid % 2][1]);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");

}

static void	handle_last(char *output_file, int pipe_fd[2][2],
	t_cmds *cmd, int cur_pid)
{
	int	file_fd;

	unlink(output_file);
	file_fd = open(output_file, O_CREAT | O_WRONLY, 0644);
	if (file_fd == -1)
		return (perror(""));
	dup2(pipe_fd[cur_pid % 2 == 0][0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	close_pipes(pipe_fd);
	close(file_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");
}

static void	pipex(char *input_file, char *output_file, t_cmds *cmds,
	int cmd_amt)
{
	int	pipe_fd[2][2];
	int	*pids;
	int	cur_pid;

	cur_pid = 0;
	ft_printf("Commands amount : %d\n", cmd_amt);
	init_pipes_and_pids(pipe_fd, &pids, cmd_amt);
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_first(input_file, cmds, pipe_fd));
	dup2(pipe_fd[0][0], STDIN_FILENO);
	wait(NULL);
	cmds = cmds->next;
	while (++cur_pid < cmd_amt - 1)
	{
		pipe(pipe_fd[cur_pid % 2]);
		pids[cur_pid] = fork();
		ft_printf("PID : %d\n", pids[cur_pid]);
		if (pids[cur_pid] == 0)
			return (handle_command(pipe_fd, cmds, cur_pid));
		dup2(pipe_fd[cur_pid % 2][0], STDIN_FILENO);
		cmds = cmds->next;
		wait(NULL);
	}
	ft_printf("fgoerogoe\n");
	pids[cur_pid] = fork();
	if (pids[cur_pid] == 0)
		return (handle_last(output_file, pipe_fd, cmds, cur_pid));
	close_pipes(pipe_fd);
	ft_printf("fgoerogoe\n");
	wait(NULL);
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

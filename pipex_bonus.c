/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:51:51 by truello           #+#    #+#             */
/*   Updated: 2024/01/08 16:58:32 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first(char *input_file, t_cmds *cmd, int output_fd,
	int **pipes)
{
	int	fd;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		perror("");
	dup2(fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(fd);
	close(output_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");
}

static void	handle_command(int input_fd, t_cmds *cmd, int output_fd,
	int **pipes)
{
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(input_fd);
	close(output_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");
}

static void	handle_last(char *output_file, int input_fd, t_cmds *cmd,
	int **pipes)
{
	int	fd;

	ft_printf("fmrjpgre\n");
	unlink(output_file);
	fd = open(output_file, O_CREAT | O_WRONLY, 0644);
	dup2(input_fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(input_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");
}

static void	pipex(char *input_file, char *output_file, t_cmds *cmds)
{
	int	**pipes;
	int	*pids;
	int	cur_pipe;

	cur_pipe = 0;
	if (init_pipes(pipes, get_cmds_amt(cmds)) == 0)
		return (ft_printf("Error while creating the pipes!\n"), (void) 0);
	pids = (int *) ft_calloc(get_cmds_amt(cmds), sizeof(int));
	if (pids == NULL)
		return (ft_printf("Malloc error for pids!\n"), (void) 0);
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_first(input_file, cmds, pipes[1][0], pipes));
	wait(NULL);
	cmds = cmds->next;
	while (++cur_pipe < get_cmds_amt(cmds) - 1)
	{
		pids[cur_pipe] = fork();
		if (pids[cur_pipe] == 0)
			return (handle_command(pipes[cur_pipe][0], cmds,
				pipes[cur_pipe + 1][0], pipes));
		waitpid(pids[cur_pipe], NULL, 0);
		cmds = cmds->next;
	}
	pids[cur_pipe] = fork();
	if (pids[cur_pipe] == 0)
		return (handle_last(output_file, pipes[cur_pipe][0], cmds, pipes));
	close_pipes(pipes);
	waitpid(pids[cur_pipe], NULL, 0);
	ft_printf("fejghjghiow\n");
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
				return (pipex(av[1], av[ac], cmds), free_cmds(cmds), 0);
			else
			{
				unlink(av[ac - 1]);
				fd = open(av[4], O_CREAT | O_APPEND | O_WRONLY, 0644);
				close(fd);
			}
		}
		else
			perror(av[1]);
	}
	return (0);
}

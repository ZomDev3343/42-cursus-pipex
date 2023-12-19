/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:13:22 by truello           #+#    #+#             */
/*   Updated: 2023/12/19 15:40:49 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first_command(char *input_file, t_cmds *cmd, int fd[2])
{
	int		file_fd;

	file_fd = open(input_file, O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");
}

static void	handle_second_command(char *output_file, t_cmds *cmd, int fd[2])
{
	int		file_fd;

	unlink(output_file);
	file_fd = open(output_file, O_CREAT | O_WRONLY, 0644);
	dup2(file_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_fd);
	if (execve(cmd->cmd_file, cmd->cmd_args, NULL) == -1)
		perror("");
}

static void	pipex(char *input_file, char *output_file, t_cmds **cmds)
{
	int		fd[2];
	int		pids[2];
	t_cmds	*cur_cmd;

	cur_cmd = *cmds;
	if (pipe(fd) == -1)
		return (ft_printf("Error while creating the pipe!\n"), (void) 0);
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_first_command(input_file, cur_cmd, fd));
	waitpid(pids[0], NULL, 0);
	cur_cmd = cur_cmd->next;
	pids[1] = fork();
	if (pids[1] == 0)
		return (handle_second_command(output_file, cur_cmd, fd));
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[1], NULL, 0);
	free_cmds(*cmds);
}

int	main(int ac, char **av, char **env)
{
	int		fd;
	t_cmds	*cmds;

	if (ac != 5)
		ft_printf("Usage : ./pipex file1 cmd1 cmd2 file2\n");
	else
	{
		if (!access(av[1], 0))
		{
			cmds = NULL;
			if (get_commands(ac, av, get_path(env), &cmds))
				pipex(av[1], av[4], &cmds);
			else
			{
				unlink(av[4]);
				fd = open(av[4], O_CREAT | O_APPEND | O_WRONLY, 0644);
				close(fd);
			}
		}
		else
			perror(av[1]);
	}
	return (0);
}

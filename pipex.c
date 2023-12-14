/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:13:22 by truello           #+#    #+#             */
/*   Updated: 2023/12/14 17:00:50 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_usage(void)
{
	ft_printf("Usage : ./pipex file1 cmd1 cmd2 file2\n");
}

static void	handle_first_command(char *input_file, char **cmd, int fd[2]
	, char *path)
{
	int		file_fd;
	char	*cmd_file;

	cmd_file = get_cmd_file(cmd[0], path);
	if (cmd_file == NULL)
		return (ft_printf("Invalid command!\n"), (void) 0);
	file_fd = open(input_file, O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_fd);

	if (execve(cmd_file, cmd, NULL) == -1)
		return (free(cmd_file),
			perror("Error while calling the first command!\n"));
}

static void	handle_second_command(char *output_file, char **cmd, int fd[2]
	, char *path)
{
	int		file_fd;
	char	*cmd_file;

	cmd_file = get_cmd_file(cmd[0], path);
	if (cmd_file == NULL)
		return (ft_printf("Invalid command!\n"), (void) 0);
	file_fd = open(output_file, O_WRONLY);
	dup2(file_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_fd);

	if (execve(cmd_file, cmd, NULL) == -1)
		return (free(cmd_file),
			perror("Error while calling the first command!\n"));
}

static void	pipex(char **args, char **env)
{
	int		fd[2];
	int		pids[2];
	char	**cmd_parts;
	char	*path;

	if (pipe(fd) == -1)
		return (ft_printf("Error while creating the pipe!\n"), (void) 0);
	path = get_path(env);
	cmd_parts = ft_split(args[2], ' ');
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_first_command(args[1], cmd_parts, fd, path));
	waitpid(pids[0], NULL, 0);
	free_parts(cmd_parts);
	cmd_parts = ft_split(args[3], ' ');
	pids[1] = fork();
	if (pids[1] == 0)
		return (handle_second_command(args[4], cmd_parts, fd, path));
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[1], NULL, 0);
	free_parts(cmd_parts);
	if (!pids[0] && pids[1])
		free(path);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		print_usage();
	else
	{
		pipex(av, env);
	}
	return (0);
}

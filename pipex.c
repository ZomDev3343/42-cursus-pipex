/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:13:22 by truello           #+#    #+#             */
/*   Updated: 2023/12/18 12:39:15 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_usage(void)
{
	ft_printf("Usage : ./pipex file1 cmd1 cmd2 file2\n");
}

static void	handle_first_command(char *input_file, char *cmd, int fd[2]
	, char *path)
{
	int		file_fd;
	char	*cmd_file;
	char	**cmd_parts;

	cmd_parts = ft_split(cmd, ' ');
	cmd_file = get_cmd_file(cmd_parts[0], path);
	if (cmd_file == NULL)
		return (free_parts(cmd_parts),
			ft_printf("Invalid command!\n"), (void) 0);
	file_fd = open(input_file, O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_fd);
	if (execve(cmd_file, cmd_parts, NULL) == -1)
		return (free(cmd_file), free_parts(cmd_parts),
			perror("Error while calling the first command!\n"));
}

static void	handle_second_command(char *output_file, char *cmd, int fd[2]
	, char *path)
{
	int		file_fd;
	char	*cmd_file;
	char	**cmd_parts;

	cmd_parts = ft_split(cmd, ' ');
	cmd_file = get_cmd_file(cmd_parts[0], path);
	if (cmd_file == NULL)
		return (free_parts(cmd_parts),
			ft_printf("Invalid command!\n"), (void) 0);
	file_fd = open(output_file, O_WRONLY);
	dup2(file_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file_fd);
	if (execve(cmd_file, cmd_parts, NULL) == -1)
		return (free(cmd_file), free_parts(cmd_parts),
			perror("Error while calling the first command!\n"));
}

static void	pipex(char **args, char **env)
{
	int		fd[2];
	int		pids[2];
	char	*path;

	if (pipe(fd) == -1)
		return (ft_printf("Error while creating the pipe!\n"), (void) 0);
	path = get_path(env);
	pids[0] = fork();
	if (pids[0] == 0)
		return (handle_first_command(args[1], args[2], fd, path));
	waitpid(pids[0], NULL, 0);
	pids[1] = fork();
	if (pids[1] == 0)
		return (handle_second_command(args[4], args[3], fd, path));
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[1], NULL, 0);
	if (!pids[0] && pids[1])
		free(path);
}

int	main(int ac, char **av, char **env)
{
	int		fd;

	if (ac != 5)
		print_usage();
	else
	{
		if (check_files(av[1], av[4]))
		{
			if (check_cmds(ac, av))
				pipex(av, env);
			else
			{
					if (access(av[4], 0))
					{
						fd = open(av[4], O_CREAT | O_WRONLY);
						char c = 127;
						write(fd, &c, 1);
						close(fd);
					}
			}
		}
	}
	return (0);
}

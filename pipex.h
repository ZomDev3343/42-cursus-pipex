/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:16:25 by truello           #+#    #+#             */
/*   Updated: 2024/01/10 16:40:07 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_cmds
{
	char			*cmd_file;
	char			**cmd_args;
	struct s_cmds	*next;
}	t_cmds;

int		check_input(char *input);
int		check_args(int ac, char **av);
int		check_cmds(int ac, char **av);
char	*get_path(char **env);
char	*get_cmd_file(char *cmd_name, char *path);
void	free_cmds(t_cmds *cmds);
t_cmds	*newcmd(char *cmd_file, char **cmd_args);
void	pbcmd(t_cmds **parent, t_cmds *child);
int		get_commands(int ac, char **av, char *path, t_cmds **cmds);

/* Bonus */

int		choose_pipex_mode(char **av, int ac, char **env, t_cmds **cmds);
int		get_cmds_amt(t_cmds *cmds);
int		init_pipes_and_pids(int pipe_fd[2][2], int **pids, int amt);
void	close_pipes(int pipe[2][2]);
void	wait_all_pids(int *pids, int len);
void	here_doc(char *limiter, char *output_file, t_cmds *cmds, int cmd_amt);
void	handle_command(t_cmds *cmd);
void	handle_last(char *output_file, t_cmds *cmd, int write_mode);
void	pipex_bonus(char *input_file, char *output_file,
			t_cmds *cmds, int cmd_amt);

#endif

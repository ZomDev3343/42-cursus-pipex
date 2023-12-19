/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:16:25 by truello           #+#    #+#             */
/*   Updated: 2023/12/18 15:13:35 by truello          ###   ########.fr       */
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

#endif

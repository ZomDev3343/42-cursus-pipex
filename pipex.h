/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:16:25 by truello           #+#    #+#             */
/*   Updated: 2023/12/14 18:35:33 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

int		check_files(char *input, char *output);
int		check_args(int ac, char **av);
int		check_cmds(int ac, char **av);
char	*get_path(char **env);
char	*get_cmd_file(char *cmd_name, char *path);

#endif

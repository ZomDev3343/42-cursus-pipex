/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:16:25 by truello           #+#    #+#             */
/*   Updated: 2023/12/14 15:21:03 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/ft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>

char	*get_path(char **env);
char	*get_cmd_file(char *cmd_name, char *path);

#endif

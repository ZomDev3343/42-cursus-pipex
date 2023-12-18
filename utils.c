/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:31:05 by truello           #+#    #+#             */
/*   Updated: 2023/12/15 16:31:04 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(char *input, char *output)
{
	return (!access(input, 0) && !access(output, 0));
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (av[i][0] == '\0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_cmds(int ac, char **av)
{
	int	i;

	i = 2;
	while (i < ac - 1)
	{
		if (av[i][0] == '\0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*get_path(char **env)
{
	while (*env)
	{
		if (ft_strncmp("PATH", *env, 4))
			return ((*env) + 5);
		env++;
	}
	return (NULL);
}

char	*get_cmd_file(char *cmd_name, char *path)
{
	char	**paths;
	int		i;
	char	*cmd_path;
	char	*tmp;

	i = -1;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		tmp = ft_strnewjoin(paths[i], "/");
		cmd_path = ft_strnewjoin(tmp, cmd_name);
		free(tmp);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (free_parts(paths), NULL);
}

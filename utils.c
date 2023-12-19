/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:31:05 by truello           #+#    #+#             */
/*   Updated: 2023/12/18 14:37:35 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_input(char *input)
{
	return (!access(input, 0));
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

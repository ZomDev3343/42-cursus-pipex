/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:25:45 by truello           #+#    #+#             */
/*   Updated: 2024/01/10 11:41:16 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (i + j < len && haystack[i + j]
			&& haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == 0)
				return ((char *) haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

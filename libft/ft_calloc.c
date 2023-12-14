/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:13:51 by truello           #+#    #+#             */
/*   Updated: 2023/11/10 14:50:46 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*r;
	size_t	i;

	r = malloc(count * size);
	if (!r)
		return (0);
	i = 0;
	while (i < count * size)
	{
		((unsigned char *) r)[i] = 0;
		i++;
	}
	return (r);
}

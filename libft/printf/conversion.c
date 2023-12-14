/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:25:41 by truello           #+#    #+#             */
/*   Updated: 2023/11/02 11:50:41 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*hex(unsigned long n, int n_len)
{
	const char	*hex_table = "0123456789abcdef";
	char		*res;
	int			i;

	n_len = get_n_len_base(n, 16);
	res = (char *) malloc(n_len + 1);
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	i = 0;
	while (n > 0)
	{
		res[n_len - 1 - i] = hex_table[n % 16];
		n /= 16;
		i++;
	}
	res[n_len] = '\0';
	return (res);
}

void	ft_strup(char *s)
{
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z')
			*s -= 32;
		s++;
	}
}

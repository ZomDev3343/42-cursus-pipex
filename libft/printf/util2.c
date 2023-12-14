/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:00:28 by truello           #+#    #+#             */
/*   Updated: 2023/11/08 12:15:20 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	get_sn_len(int n)
{
	long			nb;
	unsigned int	n_len;

	n_len = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		n_len++;
		nb /= 10;
	}
	return (n_len);
}

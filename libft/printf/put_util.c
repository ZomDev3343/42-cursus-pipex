/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:52:23 by truello           #+#    #+#             */
/*   Updated: 2023/10/31 17:19:32 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_putstrn(const char *str, int n)
{
	int	i;

	i = -1;
	while (++i < n && str[i])
		ft_putchar(str[i]);
	return (i);
}

void	ft_putnbrn(long n, int len)
{
	long int	nb;

	nb = n;
	if (nb < 0)
		nb *= -1;
	if (nb >= 0 && nb <= 9)
	{
		if (len > 0)
			ft_putchar('0' + nb);
	}
	else
	{
		ft_putnbrn(nb / 10, len - 1);
		ft_putnbrn(nb % 10, len - 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:46:52 by truello           #+#    #+#             */
/*   Updated: 2023/11/08 12:06:44 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	print_hexa(unsigned int n, t_bool uppercase)
{
	char	*hex_n;
	int		len;

	hex_n = hex(n, get_n_len_base(n, 16));
	if (!hex_n)
		return (0);
	if (uppercase)
		ft_strup(hex_n);
	len = ft_strlen(hex_n);
	ft_putstrn(hex_n, ft_strlen(hex_n));
	free(hex_n);
	return (len);
}

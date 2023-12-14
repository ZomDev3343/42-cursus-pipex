/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:46:39 by truello           #+#    #+#             */
/*   Updated: 2023/11/08 16:06:19 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_character(int c)
{
	ft_putchar((char) c);
	return (1);
}

int	print_string(char *s)
{
	int		print_len;
	size_t	s_len;

	if (!s)
		s = "(null)";
	s_len = ft_strlen(s);
	print_len = s_len;
	ft_putstrn(s, s_len);
	return (print_len);
}

int	print_pointer(void *ptr)
{
	char	*hex_ptr;
	int		len;

	len = 2;
	if (!ptr)
		return (write(1, "(nil)", 5));
	hex_ptr = hex((unsigned long) ptr, get_n_len_base((unsigned long) ptr, 16));
	if (!hex_ptr)
		return (0);
	len += ft_strlen(hex_ptr);
	ft_putstr("0x");
	ft_putstrn(hex_ptr, ft_strlen(hex_ptr));
	free(hex_ptr);
	return (len);
}

int	print_decimal(int n)
{
	int	len;

	len = get_sn_len(n) + (n < 0);
	if (n < 0)
		ft_putchar('-');
	ft_putnbrn(n, get_sn_len(n));
	return (len);
}

int	print_unsigned_decimal(unsigned int n)
{
	int	len;

	len = get_n_len((unsigned int)n);
	ft_putnbrn(n, get_n_len(n));
	return (len);
}

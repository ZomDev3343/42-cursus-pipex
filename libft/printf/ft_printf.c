/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:37 by truello           #+#    #+#             */
/*   Updated: 2023/11/08 12:07:35 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(t_format *format, va_list *args)
{
	if (format->specifier == 'c')
		return (print_character(va_arg(*args, int)));
	else if (format->specifier == '%')
		return (print_character('%'));
	else if (format->specifier == 's')
		return (print_string(va_arg(*args, char *)));
	else if (format->specifier == 'p')
		return (print_pointer(va_arg(*args, void *)));
	else if (format->specifier == 'd' || format->specifier == 'i')
		return (print_decimal(va_arg(*args, int)));
	else if (format->specifier == 'u')
		return (print_unsigned_decimal(va_arg(*args, unsigned int)));
	else if (format->specifier == 'x')
		return (print_hexa(va_arg(*args, unsigned int), 0));
	else if (format->specifier == 'X')
		return (print_hexa(va_arg(*args, unsigned int), 1));
	return (0);
}

static int	parse_format(const char *str, va_list *args, int *total)
{
	unsigned char	i;
	t_format		format;

	i = 0;
	format = newformat();
	if (is_specifier(str[i]))
		format.specifier = str[i];
	if (format.specifier == -1)
		return (0);
	*total += print_format(&format, args);
	return (i + 1);
}

int	ft_printf(const char *str, ...)
{
	int		total;
	va_list	args;
	int		format_len;

	total = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			format_len = parse_format(str + 1, &args, &total);
			if (format_len == 0)
				break ;
			str += format_len + 1;
		}
		else
		{
			ft_putchar(*str);
			str++;
			total++;
		}
	}
	va_end(args);
	return (total);
}

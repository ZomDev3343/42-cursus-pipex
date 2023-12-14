/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:57:43 by truello           #+#    #+#             */
/*   Updated: 2023/11/13 14:28:29 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef unsigned char	t_bool;

# define TRUE 1
# define FALSE 0

typedef struct s_format
{
	char		specifier;
}	t_format;

int				ft_printf(const char *str, ...);

/* Format */

t_bool			is_specifier(char c);
t_format		newformat(void);

/* Put utils */

void			ft_putchar(char c);
void			ft_putstr(const char *str);
int				ft_putstrn(const char *str, int n);
void			ft_putnbrn(long n, int len);

/* Conversion utils */

char			*hex(unsigned long n, int n_len);
void			ft_strup(char *s);

/* Printable Types */

int				print_character(int c);
int				print_string(char *str);
int				print_pointer(void *ptr);
int				print_decimal(int n);
int				print_integer(int n);
int				print_unsigned_decimal(unsigned int n);
int				print_hexa(unsigned int n, t_bool uppercase);

/* Util */

unsigned int	get_n_len_base(unsigned long n, unsigned int base);
unsigned int	get_n_len(unsigned long n);
unsigned int	get_sn_len(int n);
size_t			ft_strlen(const char *str);

#endif

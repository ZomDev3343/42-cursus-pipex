/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:02:43 by truello           #+#    #+#             */
/*   Updated: 2024/01/10 12:39:07 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <unistd.h>
# include <stdlib.h>
# include "printf/ft_printf.h"
# include "gnl/get_next_line_bonus.h"

# define FT_TRUE 1
# define FT_FALSE 0

void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *str, char c);
char	**free_parts(char **parts);

int		ft_isdigit(int c);
int		ft_isnum(char *str);

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strnewjoin(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strncpy(char *to_copy, size_t n);

int		ft_atoi(const char *str);
long	ft_atol(const char *str);

void	ft_error(const char *str);

void	ft_swap_int(int *a, int *b);

#endif

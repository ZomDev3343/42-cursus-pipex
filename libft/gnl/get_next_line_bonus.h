/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:44:22 by truello           #+#    #+#             */
/*   Updated: 2023/12/05 12:01:23 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl_list
{
	char				*data;
	ssize_t				read_size;
	int					fd;
	struct s_gnl_list	*next;
}	t_gnl_list;

char		*get_next_line(int fd);
int			is_line(char *str, ssize_t read_size);

void		lst_push_back(t_gnl_list **head, t_gnl_list *elem);
t_gnl_list	*flfd(t_gnl_list **head, int fd, char mode);
void		lst_clear_fd(t_gnl_list **head, int fd);
t_gnl_list	*lstnew(char *data, ssize_t read_size, int fd);
char		*strdupl(char *str, ssize_t read_size, ssize_t start);

#endif

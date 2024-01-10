/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:28:01 by truello           #+#    #+#             */
/*   Updated: 2023/12/05 12:01:57 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Returns the index of the first newline character if found
	in the string, else returns 0
*/
int	is_line(char *str, ssize_t read_size)
{
	ssize_t	i;

	if (!str || read_size == 0)
		return (-1);
	i = 0;
	while (i < read_size)
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

/* Returns the total length of the gotten line */
static ssize_t	get_line_length(t_gnl_list *line, int fd)
{
	ssize_t		len;
	ssize_t		newline_idx;
	t_gnl_list	*cur;

	cur = line;
	len = 0;
	if (!line)
		return (0);
	while (cur)
	{
		if (cur->fd == fd)
		{
			newline_idx = is_line(cur->data, cur->read_size);
			if (newline_idx >= 0)
				return (len + newline_idx + 1);
			else
				len += cur->read_size;
		}
		cur = cur->next;
	}
	return (len);
}

/* Fill the buffer with all the characters to form the line string*/
char	*make_line(t_gnl_list *lst, ssize_t len, int fd)
{
	ssize_t	i;
	ssize_t	j;
	char	*res;

	if (len == 0 || !lst)
		return (NULL);
	res = (char *) malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	i = 0;
	while (i < len)
	{
		while (lst->fd != fd)
			lst = lst->next;
		j = 0;
		while (j < lst->read_size && i + j < len)
		{
			res[i + j] = (lst->data)[j];
			j++;
		}
		lst = lst->next;
		i += j;
	}
	return (res);
}

/* Returns the well-formed read line and
	creates the remaining string node
*/
static char	*process_list(t_gnl_list **lst, int fd)
{
	char		*res;
	ssize_t		line_len;
	t_gnl_list	*remain;
	t_gnl_list	*last;
	ssize_t		nl_idx;

	remain = NULL;
	line_len = get_line_length(*lst, fd);
	res = make_line(*lst, line_len, fd);
	if (!res)
		return (NULL);
	last = flfd(lst, fd, 'l');
	if (!*lst || !last)
	{
		free(res);
		return (NULL);
	}
	nl_idx = is_line(last->data, last->read_size);
	if (nl_idx >= 0 && nl_idx < last->read_size - 1)
		remain = lstnew(strdupl(last->data, last->read_size, nl_idx + 1),
				last->read_size - nl_idx - 1, fd);
	lst_clear_fd(lst, fd);
	if (remain)
		lst_push_back(lst, remain);
	return (res);
}

/* Main function to do the get_next_line */
char	*get_next_line(int fd)
{
	static t_gnl_list	*line;
	char				*readline;
	ssize_t				rs;
	t_gnl_list			*new_elem;

	if (fd == -1)
		return (NULL);
	if (line && flfd(&line, fd, 'x'))
		return (process_list(&line, fd));
	readline = (char *) malloc(BUFFER_SIZE);
	if (!readline)
		return (NULL);
	rs = read(fd, readline, BUFFER_SIZE);
	while (rs > 0)
	{
		new_elem = lstnew(strdupl(readline, rs, 0), rs, fd);
		lst_push_back(&line, new_elem);
		if (is_line(readline, rs) >= 0)
			break ;
		rs = read(fd, readline, BUFFER_SIZE);
	}
	free(readline);
	if (rs == -1 || !new_elem)
		lst_clear_fd(&line, fd);
	return (process_list(&line, fd));
}

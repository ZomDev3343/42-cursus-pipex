/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:02:15 by truello           #+#    #+#             */
/*   Updated: 2024/01/11 15:24:01 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	add_line(char *line, char **file_content, char **tmp)
{
	if (!*file_content)
	{
		*file_content = ft_strnewjoin(line, "");
		free(line);
	}
	else
	{
		*tmp = ft_strnewjoin(*file_content, line);
		free(*file_content);
		free(line);
		*file_content = *tmp;
	}
}

static void	cut_limiter(char *line, char *limiter,
	char **file_content, char **tmp)
{
	char			*offset;
	unsigned int	cropped_len;
	char			*to_join;

	offset = ft_strnstr(line, limiter, ft_strlen(line));
	cropped_len = offset - line;
	to_join = ft_strncpy(line, cropped_len);
	*tmp = ft_strnewjoin(*file_content, to_join);
	free(*file_content);
	free(line);
	free(to_join);
	*file_content = *tmp;
}

static void	get_here_doc_data(char **file_content, char *limiter)
{
	char	*tmp;
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (!ft_strnstr(line, limiter, ft_strlen(line)))
			add_line(line, file_content, &tmp);
		else
		{
			cut_limiter(line, limiter, file_content, &tmp);
			break ;
		}
		line = get_next_line(0);
	}
}

static void	write_here_doc(int fd[2], char *file_content)
{
	int	idx;
	int	content_len;

	idx = 0;
	content_len = ft_strlen(file_content);
	while (idx < content_len - 1)
		idx += write(fd[1], file_content + idx, 1024);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

void	here_doc(char *limiter, char *output_file, t_cmds **cmds, int cmd_amt)
{
	char	*file_content;
	int		fd[2];
	t_cmds	*cmd;

	cmd = *cmds;
	file_content = NULL;
	get_here_doc_data(&file_content, limiter);
	if (pipe(fd) == -1)
		return (perror(""), free(file_content), free_cmds(*cmds));
	write_here_doc(fd, file_content);
	while (cmd_amt-- > 1)
	{
		handle_command(cmd);
		cmd = cmd->next;
	}
	handle_last(output_file, cmd, O_APPEND);
}

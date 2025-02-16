/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:44:41 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/16 19:21:29 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_file_name(void)
{
	char	*file;
	char	*n;

	n = ft_malloc(1, ALLOC);
	file = ft_itoa((long)n);
	file = ft_strjoin("/tmp/.tmp", file);
	if (!file)
		return (NULL);
	return (file);
}

int	read_and_write(char *del, int fd_out)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			return (close(fd_out), 0);
		tmp = ft_strchr(line, '\n');
		if (tmp)
			*tmp = '\0';
		if (!ft_strncmp(line, del, ft_strlen(line)))
			return (close(fd_out), 0);
		write(fd_out, line, ft_strlen(line));
		write(fd_out, "\n", 1);
	}
	close(fd_out);
	return (1);
}

int	get_fd(char *del)
{
	char	*file;
	int		fd_in;
	int		fd_out;

	file = get_file_name();
	if (!file)
		return (-1);
	fd_out = open(file, O_RDWR | O_CREAT, 0777);
	if (fd_out == -1)
		return (-1);
	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
		return (close(fd_out), -1);
	unlink(file);
	read_and_write(del, fd_out);
	return (fd_in);
}

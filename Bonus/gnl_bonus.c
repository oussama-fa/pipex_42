/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 09:03:38 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_linis(char *str)
{
	char	*ret;
	int		count;
	int		i;

	if (!str || !*str)
		return (NULL);
	count = 0;
	while (str[count] != '\n' && str[count])
		count++;
	if (str[count] == '\n')
		count++;
	ret = ft_malloc(count + 1, ALLOC);
	i = 0;
	while (i < count)
		ret[i++] = *(str++);
	ret[i] = '\0';
	return (ret);
}

static char	*get_rest(char *str)
{
	if (!str)
		return (NULL);
	while (*str != '\n' && *str)
		str++;
	if (*str == '\n')
		str++;
	return (ft_strdup_gnl(str));
}

static char	*read_to_rest(int fd, char *rest)
{
	char	*temp;
	int		rd;

	temp = ft_malloc((size_t)BUFFER_SIZE + 1, ALLOC);
	if (!temp)
		return (free(rest), NULL);
	while (!ft_strchr_gnl(rest, '\n'))
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd == -1)
			return (free(temp), free(rest), NULL);
		if (rd == 0)
			break ;
		temp[rd] = '\0';
		rest = ft_strjoin_gnl(rest, temp);
	}
	free(temp);
	return (rest);
}

static char	*extract_line(char **rest)
{
	char	*line;
	char	*temp;

	line = get_linis(*rest);
	if (!line)
		return (free(*rest), *rest = NULL, NULL);
	temp = *rest;
	*rest = get_rest(*rest);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_to_rest(fd, rest);
	if (!rest)
		return (NULL);
	return (extract_line(&rest));
}

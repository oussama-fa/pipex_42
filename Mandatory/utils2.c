/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:18:35 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/17 16:32:55 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	clear_fds(int fd, int save)
{
	static int	fds[2];
	static int	i;

	if (save)
	{
		if (i < 2)
		{
			fds[i] = fd;
			i++;
		}
	}
	else
	{
		scls(fds[0]);
		scls(fds[1]);
	}
	return (1);
}

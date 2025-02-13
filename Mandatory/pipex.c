/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:55 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 04:09:20 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files(int ac, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(av[ac -1], O_CREAT | O_WRONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_exec	*head;
	t_exec	*tmp;
	char	*path;
	int		i;

	if (ac != 5 || !check_files(ac, av))
		return (-1);
	path = get_path(env);
	i = 2;
	head = NULL;
	while (i < ac - 1)
	{
		tmp = set_up(av[i]);
		add_back(&head, tmp);
		i++;
	}
	exec(head, ac, av, path);
}

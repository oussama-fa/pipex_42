/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:55 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/16 19:13:38 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ignore_first_cmd(int res, int get)
{
	static int	ret;

	if (!get)
		ret = res;
	return (ret);
}

int	is_files_opened(int fail)
{
	static int	status = 1;

	if (fail)
		status = 0;
	return (status);
}

int	check_files(int ac, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ignore_first_cmd(1, 0);
		perror("pipex ");
	}
	close(fd);
	fd = open(av[ac -1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		is_files_opened(1);
		perror("pipex ");
	}
	close(fd);
	return (1);
}

void	final(t_exec *head, int ac, char **av, char *path)
{
	int	ret;

	ret = exec(head, ac, av, path);
	if (ret == 0 && !is_files_opened(0))
		ft_malloc(1, CLEAR);
	ft_malloc(ret, CLEAR);
}

int	main(int ac, char **av, char **env)
{
	t_exec	*head;
	t_exec	*tmp;
	char	*path;
	int		i;

	if (ac != 5)
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	if (!check_files(ac, av))
		return (1);
	path = get_path(env);
	i = 2;
	head = NULL;
	while (i < ac - 1)
	{
		tmp = set_up(av[i]);
		add_back(&head, tmp);
		i++;
	}
	final(head, ac, av, path);
	return (0);
}

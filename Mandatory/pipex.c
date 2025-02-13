/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:55 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 02:25:12 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		tmp = set_up(av[i], path);
		add_back(&head, tmp);
		i++;
	}
	exec(head, ac, av, path);
}

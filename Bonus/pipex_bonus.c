/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:49:17 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 02:41:14 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_exec	*head;
	t_exec	*tmp;
	char	*path;
	int		her_doc;
	int		i;

	her_doc = 0;
	if (ac >= 6 && !strcmp("here_doc", av[1]))
		her_doc = 1;
	if (ac < 5 || !check_files(ac, av, her_doc))
		return (-1);
	path = get_path(env);
	i = 2;
	if (her_doc)
		i++;
	head = NULL;
	while (i < ac - 1)
	{
		tmp = set_up(av[i], path);
		add_back(&head, tmp);
		i++;
	}
	if (her_doc)
	{
		head->fd_in = get_fd(av[2]);
		head->here_doc = 1;
	}
	exec(head, ac, av, path);
}

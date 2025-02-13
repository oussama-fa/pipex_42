/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:10:29 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 02:15:08 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec(t_exec *head, int ac, char **av, char *path)
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	fd[2];
	int	pid;

	i = 0;
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY, 0777);
	while (head)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return (close(fd[0]), close(fd[1]), close(fd_in), close(fd_out), 0);
		if (pid == 0)
		{
			if (!head->next)
			{
				close(fd[1]);
				fd[1] = fd_out;
			}
			if (!i)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			head->cmd = get_cmd_path(head->cmd, path);
			execve(head->cmd, head->opt, NULL);
			perror("pipex");
			exit(errno);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			head = head->next;
			i++;
		}
	}
	while (wait(NULL) != -1)
		;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:10:29 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 08:57:29 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_exit_status(void)
{
	int	status;
	int	check;

	while (wait(&status) != -1)
	{
		check = status;
	}
	if (WIFSIGNALED(check) || WEXITSTATUS(check) != 0)
		return (-1);
	return (0);
}

void	parent_thing(int *fd, t_exec **head, int *i)
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	*head = (*head)->next;
	(*i)++;
}

void	setup_child(int *fd, char *path, t_exec *head, t_fds *fds)
{
	if (!head->next)
	{
		close(fd[1]);
		fd[1] = fds->out;
	}
	if (!fds->i)
	{
		dup2(fds->in, 0);
		close(fds->in);
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	head->cmd = get_cmd_path(head->cmd, path);
}

int	exec(t_exec *head, int ac, char **av, char *path)
{
	t_fds	fds;
	int		fd[2];
	int		pid;

	(1) && (fds.i = 0, fds.in = open(av[1], O_RDONLY));
	fds.out = open(av[ac - 1], O_CREAT | O_WRONLY, 0777);
	while (head)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return (close(fd[0]), close(fd[1]),
				close(fds.in), close(fds.out), 0);
		if (pid == 0)
		{
			setup_child(fd, path, head, &fds);
			execve(head->cmd, head->opt, NULL);
			perror("pipex");
			exit(errno);
		}
		else
			parent_thing(fd, &head, &fds.i);
	}
	return (check_exit_status());
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:33:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/17 14:17:18 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	parent_thing(int *fd, t_exec **head, int *i)
{
	if (dup2(fd[0], 0) == -1)
		perror("dup2");
	close(fd[0]);
	close(fd[1]);
	*head = (*head)->next;
	(*i)++;
}

int	check_exit_status(void)
{
	int	status;
	int	check;

	while (wait(&status) != -1)
	{
		check = status;
	}
	return (WEXITSTATUS(check));
}

void	call_execve(t_exec *head, int i)
{
	if (!ignore_first_cmd(0, 1) || i > 0)
		execve(head->cmd, head->opt, NULL);
	else
		exit(0);
}

int	exec(t_exec *head, int ac, char **av, char *path)
{
	t_fds	fds;
	int		fd[2];
	int		pid;

	(1) && (fds.i = 0, fds.in = 0, fds.out = 1);
	innit_fds(&fds, head, ac, av);
	while (head)
	{
		if (pipe(fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			return (close(fd[0]), close(fd[1]),
				close(fds.in), close(fds.out), 0);
		if (pid == 0)
		{
			setup_child(fd, path, head, &fds);
			call_execve(head, fds.i);
			perror("pipex");
			exit(errno);
		}
		else
			parent_thing(fd, &head, &fds.i);
	}
	return (close(fds.in), close(fds.out), check_exit_status());
}

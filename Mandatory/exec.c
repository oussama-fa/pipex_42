/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:10:29 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/17 17:03:59 by oufarah          ###   ########.fr       */
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
	return (WEXITSTATUS(check));
}

int	parent_thing(int *fd, t_exec **head, int *i)
{
	if (dup2(fd[0], 0) == -1)
		perror("dup2");
	close(fd[0]);
	close(fd[1]);
	*head = (*head)->next;
	(*i)++;
	return (1);
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
		if (dup2(fds->in, 0) == -1)
			perror("dup2");
		close(fds->in);
	}
	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
		perror("dup2");
	close(fd[1]);
	head->cmd = get_cmd_path(head->cmd, path);
}

void	call_execve(t_exec *head, int i)
{
	if (!ignore_first_cmd(0, 1) || i > 0)
		execve(head->cmd, head->opt, NULL);
	else
		ft_malloc(1, CLEAR);
}

int	exec(t_exec *head, int ac, char **av, char *path)
{
	t_fds	fds;
	int		fd[2];
	int		pid;

	(1) && (fds.i = 0, fds.in = open(av[1], O_RDONLY));
	fds.out = open(av[ac - 1], O_CREAT | O_WRONLY, 0777);
	(1) && (clear_fds(fds.in, 1), clear_fds(fds.out, 1));
	while (head)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), ft_malloc(0, CLEAR), 1);
		pid = fork();
		if (pid == -1)
			return (close(fd[0]), close(fd[1]), \
				perror("fork"), ft_malloc(0, CLEAR), 0);
		if (pid == 0)
		{
			setup_child(fd, path, head, &fds);
			call_execve(head, fds.i);
			perror("pipex");
			exit(errno);
		}
		(pid) && (parent_thing(fd, &head, &fds.i));
	}
	return (check_exit_status());
}

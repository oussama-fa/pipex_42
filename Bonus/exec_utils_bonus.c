/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:34:15 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/17 14:17:23 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	innit_fds(t_fds *fds, t_exec *head, int ac, char **av)
{
	if (head->here_doc)
	{
		fds->in = head->fd_in;
		fds->out = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	else
	{
		fds->in = open(av[1], O_RDONLY);
		fds->out = open(av[ac - 1], O_CREAT | O_WRONLY, 0777);
	}
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	exit(127);
}

char	*get_cmd_path(char *cmd, char *path)
{
	char	**arr;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		cmd_not_found(cmd);
		return (NULL);
	}
	arr = ft_split(path, ':');
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		tmp = ft_strjoin(arr[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		i++;
	}
	cmd_not_found(cmd);
	return (NULL);
}

t_exec	*set_up(char *arg)
{
	char	**opt;
	t_exec	*ret;
	t_list	*args;
	size_t	i;

	ret = new_node();
	args = parser(arg);
	ret->cmd = args->value;
	opt = ft_malloc((list_size(args) + 1) * sizeof(char *), ALLOC);
	i = 0;
	while (args)
	{
		opt[i] = args->value;
		args = args->next;
		i++;
	}
	opt[i] = NULL;
	ret->opt = opt;
	return (ret);
}

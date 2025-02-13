/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:34:15 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 02:33:03 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_exec	*new_node(void)
{
	t_exec	*ret;

	ret = malloc(sizeof(t_exec));
	if (!ret)
		return (NULL);
	ret->fd_in = 0;
	ret->fd_out = 1;
	ret->cmd = NULL;
	ret->opt = NULL;
	ret->here_doc = 0;
	ret->next = NULL;
	return (ret);
}

void	add_back(t_exec **head, t_exec *new)
{
	t_exec	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
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
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
		exit(127);
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
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	exit(127);
	return (NULL);
}

t_exec	*set_up(char *arg, char *path)
{
	char	**opt;
	t_exec	*ret;
	t_list	*args;
	size_t	i;

	ret = new_node();
	args = parser(arg);
	ret->cmd = args->value;
	opt = malloc((list_size(args) + 1) * sizeof(char *));
	if (!opt)
		return (NULL);
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

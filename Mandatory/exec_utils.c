/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:22:25 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/17 16:17:31 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	ft_malloc(127, CLEAR);
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (1);
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
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
	while (arr[i] && !is_empty(cmd))
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

int	scls(int fd)
{
	if (fd > 2)
		close(fd);
	return (1);
}

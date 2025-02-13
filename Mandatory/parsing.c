/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:04:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 02:20:58 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	char	*path;
	size_t	i;
	int		incr;

	i = 0;
	incr = 4;
	while (env && env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
		{
			if (env[i][incr] == '=')
				incr++;
			path = ft_strdup(env[i] + incr);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	check_files(int ac, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	fd = open(av[ac -1], O_CREAT | O_WRONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

t_list	*new_list(char *value)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

void	add_back_list(t_list **head, t_list *new)
{
	t_list	*tmp;

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

char	*joinchar(char *s, char c)
{
	char	*ret;
	int		i;

	ret = malloc(ft_strlen(s) + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	ret[++i] = '\0';
	return (ret);
}

size_t	list_size(t_list *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	handle_word(t_list **head, int *i, char *arg)
{
	char	*value;

	value = NULL;
	while (arg[*i] && arg[*i] != '\'' && arg[*i] != '\"' && !isspace(arg[*i]))
	{
		value = joinchar(value, arg[*i]);
		if (!value)
			return (0);
		(*i)++;
	}
	add_back_list(head, new_list(value));
	return (1);
}

int	handle_quotes(t_list **head, int *i, char *arg)
{
	char	*value;
	char	quote;

	value = NULL;
	quote = arg[*i];
	(*i)++;
	while (arg[*i] && arg[*i] != quote)
	{
		value = joinchar(value, arg[*i]);
		if (!value)
			return (0);
		(*i)++;
	}
	if (arg[*i] == quote)
		(*i)++;
	add_back_list(head, new_list(value));
	return (1);
}

t_list	*parser(char *arg)
{
	t_list	*head;
	int		i;

	head = NULL;
	i = 0;
	while (arg[i])
	{
		while (arg[i] && isspace(arg[i]))
			i++;
		if (arg[i] != '\'' && arg[i] != '\"')
		{
			handle_word(&head, &i, arg); // protect if 0 is returned
		}
		else if (arg[i])
		{
			handle_quotes(&head, &i, arg); // protect if 0 is returned
		}
	}
	return (head);
}

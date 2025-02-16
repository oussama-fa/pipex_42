/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:32:08 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/16 19:23:58 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **env)
{
	char	*path;
	int		incr;
	size_t	i;

	i = 0;
	incr = 4;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
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

char	*joinchar(char *s, char c)
{
	char	*ret;
	int		i;

	ret = ft_malloc(ft_strlen(s) + 2, ALLOC);
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

int	handle_word(t_list **head, int *i, char *arg)
{
	char	*value;

	value = NULL;
	while (arg[*i] && arg[*i] != '\'' && arg[*i] != '\"'
		&& !ft_isspace(arg[*i]))
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
		while (arg[i] && ft_isspace(arg[i]))
			i++;
		if (arg[i] != '\'' && arg[i] != '\"')
		{
			if (!handle_word(&head, &i, arg))
				return (NULL);
		}
		else if (arg[i])
		{
			if (!handle_quotes(&head, &i, arg))
				return (NULL);
		}
	}
	if (!head)
		head = new_list(ft_strdup(arg));
	return (head);
}

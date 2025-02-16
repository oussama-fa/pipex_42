/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:25:51 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/16 19:38:26 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*ret;
	size_t	i;

	ret = ft_malloc(ft_strlen(s) + 1, ALLOC);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 && *s1 == *s2 && --n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	ret = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, ALLOC);
	i = -1;
	j = 0;
	while (s1 && s1[++i])
		ret[i] = s1[i];
	while (s2 && s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

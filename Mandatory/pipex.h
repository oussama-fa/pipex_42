/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:05:35 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 08:53:27 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	char			*cmd;
	char			**opt;
	struct s_exec	*next;
}	t_exec;

typedef struct s_list
{
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_fds
{
	int	in;
	int	out;
	int	i;
}	t_fds;

// utils
char	*ft_strchr(char *s, char c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
int		ft_strncmp(char *s1, char *s2, size_t size);

// exec
int		exec(t_exec *head, int ac, char **av, char *path);

// list
t_exec	*new_node(void);
void	add_back(t_exec **head, t_exec *new);
t_list	*new_list(char *value);
size_t	list_size(t_list *list);
void	add_back_list(t_list **head, t_list *new);

// ft_split
char	**ft_split(char const *s, char c);

// exec_utils
char	*get_cmd_path(char *cmd, char *path);
t_exec	*set_up(char *arg);

// parsing
char	*get_path(char **env);
t_list	*parser(char *arg);
char	*joinchar(char *s, char c);
int		check_files(int ac, char **av);
int		handle_word(t_list **head, int *i, char *arg);
int		handle_quotes(t_list **head, int *i, char *arg);

#endif
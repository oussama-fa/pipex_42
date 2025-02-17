/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:29:36 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/17 14:17:39 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "garbage_bonus.h"

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	int				here_doc;
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

// parsing
int		ft_isspace(char c);
char	*get_path(char **env);
char	*joinchar(char *s, char c);
t_list	*parser(char *arg);
int		handle_word(t_list **head, int *i, char *arg);
int		handle_quotes(t_list **head, int *i, char *arg);
int		check_files(int ac, char **av, int here_doc);

// exec
int		exec(t_exec *head, int ac, char **av, char *path);
void	innit_fds(t_fds *fds, t_exec *head, int ac, char **av);

// exec utils
char	*get_cmd_path(char *cmd, char *path);
t_exec	*set_up(char *arg);

// list
t_exec	*new_node(void);
void	add_back(t_exec **head, t_exec *new);
void	add_back_list(t_list **head, t_list *new);
t_list	*new_list(char *value);
size_t	list_size(t_list *list);
int		ignore_first_cmd(int res, int get);
int		is_files_opened(int fail);

// ft_itoa
char	*ft_itoa(int n);

// ft_split
char	**ft_split(char const *s, char c);

// utils
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_strchr(char *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t size);

// gnl utils
size_t	ft_strlen(const char *s);
char	*ft_strchr_gnl(char *s, char c);
char	*ft_strdup_gnl(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);

// gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

// heredoc
char	*get_file_name(void);
int		read_and_write(char *del, int fd_out);
int		get_fd(char *del);

#endif
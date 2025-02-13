/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:58:53 by oufarah           #+#    #+#             */
/*   Updated: 2025/02/13 09:07:15 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_BONUS_H
# define GARBAGE_BONUS_H

# include <stdlib.h>

# define ALLOC 1
# define CLEAR 2

void	*ft_malloc(size_t size, int flag);

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;

}	t_garbage;

#endif
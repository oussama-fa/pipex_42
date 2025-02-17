# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/09 19:53:14 by oufarah           #+#    #+#              #
#    Updated: 2025/02/17 16:20:36 by oufarah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

CC = cc
CFLAG = -Wall -Wextra -Werror

INC = Mandatory/pipex.h
INC_GARBAGE = Mandatory/garbage.h
INC_B = Bonus/pipex_bonus.h
INC_GARBAGE_B = Bonus/garbage_bonus.h

RM = rm -f

SRC = Mandatory/exec.c Mandatory/exec_utils.c Mandatory/ft_split.c  Mandatory/parsing.c \
		Mandatory/pipex.c  Mandatory/utils.c Mandatory/list.c Mandatory/garbage.c
SRC_B = Bonus/exec_bonus.c  Bonus/exec_utils_bonus.c  Bonus/ft_itoa_bonus.c  Bonus/ft_split_bonus.c \
		Bonus/gnl_bonus.c  Bonus/gnl_utils_bonus.c  Bonus/heredoc_bonus.c  Bonus/parsing_bonus.c \
		Bonus/pipex_bonus.c Bonus/utils_bonus.c Bonus/list_bonus.c  Bonus/garbage_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

bonus : $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAG) $(OBJ_B) -o $(NAME_B) 

%.o:%.c $(INC) $(INC_GARBAGE)
	$(CC) $(CFLAG) -c $< -o $@

Bonus/%.o: Bonus/%.c $(INC_B) $(INC_GARBAGE_B)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_B)

fclean: clean
	$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONY: clean	
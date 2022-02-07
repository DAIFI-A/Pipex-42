# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 20:05:24 by adaifi            #+#    #+#              #
#    Updated: 2022/02/05 14:36:10 by adaifi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = pipex.c utils.c
SRCDIR = src
OBJS_DIR = objs
CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
LIB = -Llibft -lft
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR):
			@mkdir $@

$(OBJS_DIR)/%.o: $(SRCDIR)/%.c | $(OBJS_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
			@make -C libft
			$(CC) $(CFLAGS) $^ -o $(NAME) $(LIB)

clean:
			@rm -rf $(OBJS_DIR)
			@make -C libft clean

fclean:	clean
			@rm -f  $(NAME)
			@make -C libft fclean

re: fclean all

-include $(DEPS)

.PHONY:	clean re fclean all

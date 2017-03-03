# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aribeiro <aribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/23 10:40:19 by aribeiro          #+#    #+#              #
#    Updated: 2017/03/03 15:43:54 by aribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so

CFLAGS = -Wall -Werror -Wextra

SRC = 	mutex_lock_unlock.c \
		my_free_all.c \
		my_free_munmap.c \
		my_free.c \
		my_malloc.c \
		my_malloc_headers.c \
		my_realloc.c \
		oc_memcpy.c \
		oc_putchar_fd.c \
		oc_puthexa.c \
		oc_putnbr_fd.c \
		oc_putstr_fd.c \
		show_map.c \
		show_mem_1.c \
		show_mem_2.c \
		verif_secu.c

SRCS = $(addprefix srcs/, $(SRC))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -shared -o $(NAME) $(OBJ)
	ln -s $(NAME) $(LINK_NAME)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS) -I./includes

clean:
	rm -rf $(OBJ)

fclean:clean
	rm -rf $(NAME)
	rm -rf $(LINK_NAME)

re: fclean all

.PHONY: all clean fclean re

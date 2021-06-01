# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/31 11:42:53 by ancoulon          #+#    #+#              #
#    Updated: 2021/06/01 13:40:43 by ancoulon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

LIBDIR		= libcarbon
LIBNAME		= libcarbon.a
LIBMAKE		= make -C $(LIBDIR)

CC			= clang -g
CFLAGS		= -Wall -Wextra -Werror -I./libcarbon/include
RM			= rm -f

SRCS		= main.c utils.c

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(LIBMAKE) all
			$(CC) $(CFLAGS) -L./libcarbon -lcarbon -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(LIBMAKE) clean
			$(RM) $(OBJS)

fclean:		clean
			$(LIBMAKE) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancoulon <ancoulon@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/31 11:42:53 by ancoulon          #+#    #+#              #
#    Updated: 2021/05/31 11:43:18 by ancoulon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= clang -g
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCS		= $(wildcard *.c)

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
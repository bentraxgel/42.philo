# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seok <seok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/19 00:34:24 by seok              #+#    #+#              #
#    Updated: 2023/08/24 18:37:48 by seok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# NAME = philo
# INCD = philo.h

# SRCS = main.c library.c init.c utils.c

# OBJS = $(SRCS:.c=.o)
# $(NAME) : $(NAME)($(OBJS))

# all : $(NAME)

# clean :
# 	rm -rf $(OBJS)

# fclean : clean
# 	rm -rf $(NAME)

# re : fclean all

# .PHONY : clean fclean all re
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
NAME = philo
INCD = philo.h

SRCS = main.c library.c init.c utils.c mutex.c behavior.c monitor.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INCD)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

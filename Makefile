# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 19:29:13 by tbesson           #+#    #+#              #
#    Updated: 2022/12/08 17:42:17 by tbesson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	= sources
SRCS_NAME	= main.c			\
				check_arg.c		\
				utils.c			\
				init_dinner.c	\
				end_dinner.c	\
				lib.c			\
				philo_states.c	\
				start_dinner.c	\
				routines.c
OBJS_DIR	= objs
OBJS_NAME	= ${SRCS_NAME:.c=.o}
SRCS		= $(addprefix $(SRCS_DIR)/,$(SRCS_NAME))
OBJS		= $(addprefix $(OBJS_DIR)/,$(OBJS_NAME))
INC			= -I ./includes

NAME	= philo

CC		= gcc
RM		= rm -f
CFLAGS	= $(INC) -Wall -Wextra -Werror -pthread
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
			@mkdir $(OBJS_DIR) 2> /dev/null || true
			$(CC) $(CFLAGS) -o $@ -c $<

clean:
			@rm -rf $(OBJS) $(OBJS_DIR)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

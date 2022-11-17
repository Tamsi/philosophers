# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 16:49:59 by tbesson           #+#    #+#              #
#    Updated: 2022/08/28 02:03:13 by tamsi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_strappend.c get_next_line.c ft_printf.c args_text.c args_numbers.c args_hexa.c ft_nblen.c ft_putnbr_unsigned.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_ischarset.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_OBJS	= ${BONUS:.c=.o}
OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

HEADER	= includes/

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o $@  -I ${HEADER}

${NAME}:	${OBJS}
		ar -rcs	${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:	${OBJS} ${BONUS_OBJS}
		ar -rcs ${NAME} ${OBJS} ${BONUS_OBJS}

.PHONY:		all clean fclean re bonus

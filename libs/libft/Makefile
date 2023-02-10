# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 14:40:57 by lorobert          #+#    #+#              #
#    Updated: 2022/10/21 08:37:04 by lorobert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libft.a

SRCS	:=	ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_strchr.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memset.c \
			ft_strdup.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_itoa_hex.c \
			ft_itoa_hex_long.c \
			ft_itoa_unsigned.c \
			ft_printf.c \
			ft_printf_char.c \
			ft_printf_hex.c \
			ft_printf_int.c \
			ft_printf_ptr.c \
			ft_printf_string.c \
			ft_printf_uint.c
OBJS	:=	$(SRCS:.c=.o)

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror

RM		:=	rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

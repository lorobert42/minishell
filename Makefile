# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 10:10:10 by lorobert          #+#    #+#              #
#    Updated: 2023/03/01 11:11:34 by lorobert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell

LIBS			:=	ft
LIBS_TARGET		:=	libs/libft/libft.a

INCS			:=	include \
					libs/libft/include

SRC_DIR			:=	sources
SRCS			:=	builtins/ft_echo.c \
					builtins/ft_pwd.c \
					builtins/ft_cd.c \
					builtins/ft_env.c \
					builtins/ft_getenv.c \
					builtins/ft_export.c \
					builtins/ft_unset.c \
					env/parse_env.c \
					lexer/lexer.c
SRCS			:=	$(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR		:=	.build
OBJS			:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(OBJS:.o=.d)

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -g
CPPFLAGS		:=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS			:=	$(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS			:=	$(addprefix -l,$(LIBS))

RM				:=	rm -f
MAKEFLAGS		+=	--no-print-directory
DIR_DUP			=	mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
.SILENT:
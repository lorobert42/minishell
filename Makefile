# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 10:10:10 by lorobert          #+#    #+#              #
#    Updated: 2023/03/30 10:05:48 by lorobert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell

LIBS			:=	ft readline
LIBS_TARGET		:=	libs/libft_rework/libft.a

INCS			:=	include \
					libs/libft_rework/gnl/include \
					libs/libft_rework/libft/include \
					libs/libft_rework/printf/include \

SRC_DIR			:=	sources
SRCS			:=	builtins/ft_echo.c \
					builtins/ft_pwd.c \
					builtins/ft_cd.c \
					builtins/ft_env.c \
					builtins/ft_getenv.c \
					builtins/ft_export.c \
					builtins/ft_unset.c \
					env/parse_env.c \
					env/del_env.c \
					lexer/lexer.c \
					lexer/token.c \
					lexer/issep.c \
					expander/expander.c \
					expander/quotes.c \
					parser/parser.c \
					parser/commands.c \
					parser/token_type.c \
					parser/debug_print_command_table.c \
					utils/ft_isspace.c \
					utils/tab_utils.c \
					utils/clear_split.c \
					main/main.c \
					main/init.c \
					main/loop.c \

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
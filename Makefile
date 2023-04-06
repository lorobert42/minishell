# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 10:10:10 by lorobert          #+#    #+#              #
#    Updated: 2023/04/06 09:52:26 by lorobert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Name
GREEN			=		\033[1;32m
YELLOW			= 		\033[33m
BG_GREEN		=		\033[42m
BG_CYAN			=		\033[46m
ENDCOLOR		=		\033[0m

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
					builtins/ft_unset.c \
					builtins/ft_export.c \
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
					executer/executer.c \
					executer/heredoc.c \
					utils/execute_utils.c \
					utils/error.c \
					sig_handler/signals.c

SRCS			:=	$(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR		:=	.build
OBJS			:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(OBJS:.o=.d)

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror -g
CPPFLAGS		:=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS			:=	$(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS			:=	$(addprefix -l,$(LIBS))

# If READLINE env variable is set, use it as an extra include and
# library path.
# This is useful if we cannot install readline in the compilers include
# directory.
# export READLINE=/Users/[username]/.brew/Cellar/readline/8.2.1
ifdef READLINE
	LDFLAGS 	+= -L$(READLINE)/lib
	CPPFLAGS	+= -I$(READLINE)/include
endif

RM				:=	rm -f
MAKEFLAGS		+=	--no-print-directory
DIR_DUP			=	mkdir -p $(@D)

all: ascii $(NAME)
	@echo "\n$(GREEN)Your minishell is ready to go !$(ENDCOLOR)"

ascii:
		@tput setaf 6; cat ascii_art/minishell; tput setaf 7
		@echo "\n$(ENDCOLOR)"
		@echo "$(GREEN)Compilation de la libft !$(ENDCOLOR)"

$(NAME): $(LIBS_TARGET) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo "$(BG_CYAN)     $(ENDCOLOR)\c"

-include $(DEPS)

clean:
	@tput setaf 2; cat ascii_art/trash; tput setaf 7
	@echo "\n\n$(YELLOW) Merci pour ce merveilleux repas ! \n\t signé Le dévoreur de code. $(ENDCOLOR)"
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
.SILENT:
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:35:33 by afavre            #+#    #+#              #
#    Updated: 2022/11/21 13:55:35 by afavre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

LIBFT		= libft
GNL			= gnl
PRINTF		= printf

NAME		= libft.a
INCLUDE		= include
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRC_DIR = libft gnl printf

SRC 		= 	$(addsuffix /obj/*, $(SRC_DIR))
#OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@MAKE -C $(LIBFT)
			@MAKE -C $(GNL)
			@MAKE -C $(PRINTF)
			@$(AR) -c $(NAME) $(SRC)
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@MAKE clean -C $(LIBFT)
			@MAKE clean -C $(GNL)
			@MAKE clean -C $(PRINTF)

fclean:		clean
			@$(RM) -f $(NAME)
			@MAKE fclean -C $(LIBFT)
			@MAKE fclean -C $(GNL)
			@MAKE fclean -C $(PRINTF)

re:			fclean all

.PHONY:		all clean fclean re

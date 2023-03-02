/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/02 09:22:56 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_simple_command
{
	char	**command;
	int		ret;
}	t_simple_command;

typedef struct s_command_table
{
	t_simple_command	**commands;
	int					commands_num;
	char				*in;
	char				*out;
	char				*err;
}	t_command_table;


// LEXER
t_list	*lexer(char *command);

// BULTINS
int		ft_env(t_env *env, int fd);
char	*ft_getenv(t_env *env, char *key);
int		ft_export(t_env **env, t_env *new);
int		ft_unset(t_env **env, char *s);
int		ft_echo(char **args, int fd);
int		ft_pwd(t_env *env, int fd);

t_env	*parse_env(char **env_strs);
t_env	*extract_entry(char *env_entry);
t_env	*create_entry(char *key, char *value);

#endif

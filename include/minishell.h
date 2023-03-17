/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/17 14:19:28 by lorobert         ###   ########.fr       */
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

typedef enum e_token_type
{
	REDIR_LEFT,
	HERE_DOC,
	REDIR_RIGHT,
	REDIR_APPEND,
	PIPE,
	QUOTE_STR,
	DBL_QUOTE_STR,
	LITERAL
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

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
	t_simple_command	*commands;
	int					n_commands;
	char				*in;
	char				*out;
	char				*err;
}	t_command_table;


// LEXER
t_token	*lexer(char *command);
t_token	*create_token(char *value, t_token_type type);
void	add_token(t_token **tokens, t_token *new);
int		issep(int c);

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

// UTILS
int		ft_isspace(int c);

#endif
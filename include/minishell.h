/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/30 11:28:29 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
#include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libs/libft_rework/libft/include/libft.h"
# include "../libs/libft_rework/gnl/include/get_next_line.h"
# include "../libs/libft_rework/printf/include/ft_printf.h"

typedef enum e_token_type
{
	REDIR_LEFT,
	REDIR_RIGHT,
	HERE_DOC,
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

typedef struct s_command
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
	int		ret;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	int			n_commands;
}	t_command_table;

typedef struct s_data
{
	int				run;
	char			**env;
	t_token			*token;
	t_command_table	*table;
}	t_data;

// LEXER
t_token			*lexer(char *command);
t_token			*create_token(char *value, t_token_type type);
void			add_token(t_token **tokens, t_token *new);
void			clean_tokens(t_token *tokens);
int				issep(int c);

// BULTINS
int				ft_env(t_env *env, int fd);
void			ft_export(t_data *data, char *key, char *value);
int				ft_unset(t_env **env, char *s);
int				ft_echo(char **args, int fd);
int				ft_pwd(char **env);
int				ft_cd(char *path, t_env **env);

char			**parse_env(char **env_strs);
t_env			*extract_entry(char *env_entry);
t_env			*create_entry(char *key, char *value);
void			del_env(t_env *env);
void			del_all_env(t_env **env);

// FT_GETENV
int				get_env_index(char **env, char *key);
char			*ft_getenv(char **env, char *key);

// UTILS
int				ft_isspace(int c);

void			clear_split(char **split);

// LIST_UTILS
void			clear_lst(t_data *data);

// TAB_UTILS
int				get_tab_size(char **tab);
char			**tab_add_back(t_data *data, char *content);
void			print_str_tab(char **tab);

// CLEAR_SPLIT
void			clear_split(char **split);

// ENV_UTILS
char			*get_full_env(t_env *env, char *key);

// PARSER
t_command_table	*parser(t_token *tokens);
int				count_commands(t_token *tokens);
int				command_size(t_token *tokens);
int				is_redir(t_token_type t);
int				is_string(t_token_type t);
void			print_command_table(t_command_table *table);
void			clean_command_table(t_command_table *table);

// EXPANDER
int				expander(t_token *tokens, t_env *env);
int				is_quote(char c);
int				count_quotes(char *s);
int				check_unclosed_quotes(t_token *token);
int				delete_quotes(t_token *token);

// EXECUTER
int 			executer(t_data *data);

// EXECUTE_UTILS
char			*get_path(char *path, char *cmd);


// MAIN
void			loop(t_data *data);
void			init(t_data *data, char **env);

#endif

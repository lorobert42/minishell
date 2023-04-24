/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/24 15:36:11 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

# include "../libs/libft/include/libft.h"

typedef struct s_global
{
	int	error;
	int	status;
	int	parsing;
	int	nb_children;
}	t_global;

t_global	g_glob;

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

typedef struct s_file
{
	char			*name;
	int				append;
	struct s_file	*next;
}	t_file;

typedef struct s_command
{
	char	**args;
	t_file	*infiles;
	t_file	*outfiles;
	int		fd[2];
	int		ret;
}	t_command;

typedef struct s_command_table
{
	t_command	*commands;
	int			n_commands;
}	t_command_table;

typedef struct s_data
{
	int					run;
	int					saved_io[2];
	char				**env;
	t_token				*token;
	t_command_table		*table;
	struct sigaction	sa;
	struct termios		tp;
}	t_data;

// LEXER
t_token			*lexer(char *command);
t_token			*create_token(char *value, t_token_type type);
void			add_token(t_token **tokens, t_token *new);
void			delete_token(t_token **start, t_token *to_del);
void			clean_tokens(t_token *tokens);
int				issep(int c);

// BULTINS
int				ft_env(char **env);
char			*ft_getenv(char **env, char *key);
int				ft_export(t_data *data, char *arg);
int				print_export(char **env);
void			update_env(t_data *data, char *key, char *new_value);
int				ft_unset(t_data *data, char *s);
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_cd(t_data *data, char **args);
int				ft_exit(char **args);
char			**parse_env(char **env_strs);
int				exec_builtins(t_data *data, char **cmd);
int				is_builtins(char **cmd);

// FT_GETENV
int				get_env_index(char **env, char *key);
char			*ft_getenv(char **env, char *key);
char			*getenv_value(char **env, char *key);

// UTILS
int				ft_isspace(int c);

void			clear_split(char **split);

// LIST_UTILS
void			clear_lst(t_data *data);

// TAB_UTILS
int				get_tab_size(char **tab);
char			**tab_add_back(t_data *data, char *content);
void			print_str_tab(char **tab);
char			**sort_tab(char **env);

// CLEAR_SPLIT
void			clear_split(char **split);

// PARSER
t_command_table	*parser(t_token *tokens);
int				count_commands(t_token *tokens);
int				command_size(t_token *tokens);
int				is_redir(t_token_type t);
int				is_string(t_token_type t);
void			print_command_table(t_command_table *table);
void			clean_command_table(t_command_table *table);

// EXPANDER
int				expander(t_token *tokens, char **env);
int				is_quote(char c);
int				count_quotes(char *s);
int				check_unclosed_quotes(char *str);
char			*delete_quotes(char *str);
int				check_expansion(char **str, char **env);

// EXECUTER
int				execute(t_data *data);
int				heredoc(char **delim, int fd, t_data *data);
void			set_heredoc(t_data *data);
void			close_pipe(t_data *data, int i);
int				redir_pipe(t_data *data, int i);
int				redir_file_in(t_data *data, int i);
int				redir_file_out(t_data *data, int i);
void			delete_heredoc(t_data *data, int i);
void			close_redirections(t_data *data, int i);

// EXECUTE_UTILS
char			*get_path(char *path, char *cmd);

// SIGNAUX
void			sig_handler(void);
void			termios_remove_ctrl(void);
void			termios_restore_ctrl(void);

// MAIN
void			loop(t_data *data);
void			init(t_data *data, char **env);

// ERROR
void			print_error(char *msg, char *command);

#endif

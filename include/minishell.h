/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/11 12:53:54 by lorobert         ###   ########.fr       */
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
# include <dirent.h>

# include "../libs/libft_rework/libft/include/libft.h"
# include "../libs/libft_rework/gnl/include/get_next_line.h"
# include "../libs/libft_rework/printf/include/ft_printf.h"

typedef struct s_global
{
	int	error;
	int	status;
	int	parsing;
	int	nb_children;
}	t_global;

extern t_global	g_glob;

typedef enum e_token_type
{
	REDIR_LEFT,
	REDIR_RIGHT,
	HERE_DOC,
	REDIR_APPEND,
	PIPE,
	QUOTE_STR,
	DBL_QUOTE_STR,
	LITERAL,
	IGNORE
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
	int		fd_in;
	int		fd_out;
	pid_t	pid;
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
	struct sigaction	old_sa;
}	t_data;

// BULTINS
// ---> check_builtins.c
int				is_builtins(char **cmd);
int				exec_builtins(t_data *data, char **cmd);
// ---> ft_cd.c
int				ft_cd(t_data *data, char **args);
// ---> ft_echo.c
int				ft_echo(char **args);
// ---> ft_env.c
int				ft_env(char **env);
// ---> ft_exit.c
int				ft_exit(char **args, t_data *data);
// ---> ft_export.c
int				print_export(char **env);
void			update_env(t_data *data, char *key, char *new_value);
int				ft_export(t_data *data, char **arg);
int				is_valid_key(char *args);
char			*create_env_value(char *key, char *value);
// ---> ft_getenv.c
char			*getenv_value(char **env, char *key);
int				get_env_index(char **env, char *key);
char			*ft_getenv(char **env, char *key);
// ---> ft_pwd.c
int				ft_pwd(char **env);
// ---> ft_unset.c
int				ft_unset(t_data *data, char **s);

// ENV
// ---> parse_env.c
char			**parse_env(char **env_strs);

// EXECUTER
// --> executer.c
void			check_access(char *path);
void			children(t_data *data, int i);
int				execute(t_data *data);
// --->heredoc.c
int				set_heredoc(t_data *data);
int				heredoc(char **delim, int fd, t_data *data);
void			heredoc_loop(t_data *data, char **delim, int expand, int fd);
// ---> redirection.c
int				redir_file_in(t_data *data, int i);
int				redir_file_out(t_data *data, int i);

// EXPANDER
// ---> expander.c
void			check_expansion(char **str, char **env);
int				expander(t_token *tokens, char **env);
// --->quotes.c
int				is_quote(char c);
int				count_quotes(char *s);
int				check_unclosed_quotes(char *str);
char			*delete_quotes(char *str);
// ---> expand_var.c
int				expand_token(char **str, int pos, int in_quotes, char **env);

// LEXER
// ---> char_type.c
int				issep(int c);
t_token_type	quote_type(char c);
// ---> lexer.c
t_token			*lexer(char *command);
// ---> token.c
t_token			*create_token(char *value, t_token_type type);
void			add_token(t_token **tokens, t_token *new);
t_token			*delete_token(t_token *start, t_token *to_del);
void			clean_tokens(t_token *tokens);

// MAIN
// ---> init.c
void			init(t_data *data, char **env);
// ---> loop.c
void			loop(t_data *data);
int				setup_loop(t_data *data, char *buffer);
// ---> inline_arg.c
void			inline_arg(t_data *data, char **av);

// PARSER
// ---> commands.c
t_command_table	*init_table(t_token *tokens);
void			init_commands(t_command_table *table);
int				count_commands(t_token *tokens);
int				command_size(t_token *tokens);
void			clean_command_table(t_command_table *table);
// ---> debug_print_command_table.c
void			print_command_table(t_command_table *table);
// ---> parser.c
t_command_table	*parser(t_token *tokens);
t_token			*extract_redirections(t_token *tokens, t_command *command);
t_token			*extract_strings(t_token *tokens, t_command *command);
// ---> token_type.c
int				is_redir(t_token_type t);
int				is_string(t_token_type t);

// SIG_HANDLER
// ---> signals.c
void			sig_handler(t_data *data);
void			sig_restore(t_data *data);
void			heredoc_handler(void);
void			sig_ignore(void);
// ---> termios.c
void			termios_remove_ctrl(void);
void			termios_restore_ctrl(void);

// UTILS
// ---> clear_split.c
void			clear_split(char **split);
// --> debug.c
void			print_str_tab(char **str);
// ---> error.c
void			print_error(char *msg, char *command);
void			fatal_error(char *msg, char *command, int code);
// ---> execute_utils.c
char			*get_path(char *path, char *cmd);
int				inside_exec(t_data *data);
void			init_and_exec_children(t_data *data, int i);
void			check_status(int status);
char			*utils_path(t_data *data, char *env, int num);
// ---> export_utils.c
char			**set_export_option(char *arg);
// ---> ft_isspace.c
int				ft_isspace(int c);
// ---> heredoc_utils.c
void			heredoc_child(char **delim, int fd, int expand, t_data *data);
int				heredoc_parent(pid_t pid, t_data *data);
// ---> list_utils.c
void			clear_lst(t_data *data);
// --->tab_utils.c
int				get_tab_size(char **tab);
void			print_str_tab(char **tab);
char			**tab_add_back(t_data *data, char *content);
char			**sort_tab(char **env);
// --->redirections_utils.c
void			close_all_pipes(t_data *data, int i);
void			close_redirections(t_data *data, int i);
void			restore_stdio(t_data *data);
void			delete_heredoc(t_data *data, int i);
int				redir_pipe(t_data *data, int i);
// --->exit_utils.c
char			*remove_zero(char *nb);

#endif

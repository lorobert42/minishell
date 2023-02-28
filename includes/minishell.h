/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/24 11:21:14 by lorobert         ###   ########.fr       */
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
# include "ft_printf.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char	*name;
	char	**args;
	char	*in;
	char	*out;
	char	*err;
	int		ret;
}	t_command;

typedef struct s_readline
{
	char	*cmd1d;
	char	**cmd2d;
	char	*pwd;
	char	*uname;
	char	*display;
}	t_readline;

// BULTINS
int		ft_env(t_env *env, int fd);
char	*ft_getenv(t_env *env, char *key);
int		ft_export(t_env **env, t_env *new);
int		ft_unset(t_env **env, char *s);
int		ft_echo(char **args, int fd);
int		ft_pwd(t_env *env, int fd);
int		ft_cd(char *path, t_env **env);

t_env	*parse_env(char **env_strs);
t_env	*extract_entry(char *env_entry);
t_env	*create_entry(char *key, char *value);


//parsing
char		**ft_cmdparsing(char *cmd);
t_command	ft_addargs(char **cmd);
char		**ft_parsingargs(char **args, int nbr);
int			ft_findcmdp1(t_command *cmd, t_env *env);
void		ft_mainloop(t_env *env);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:41:03 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/15 16:38:46 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
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

// BULTINS
int	ft_env(t_env *env, int fd);
int	ft_echo(char **args, int fd);
int	ft_export(t_env **env, char *s);
int	ft_pwd(t_env *env, int fd);

t_env	*parse_env(char **env_strs);
t_env	*extract_entry(char *env_entry);

#endif

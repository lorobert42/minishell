/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:11:34 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/17 16:59:38 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_ifexist(t_data *data, char *key, char *newval)
{
	char	*oldval;

	oldval = ft_getenv(data->env, key);
	if (oldval)
	{
		update_env(data, key, newval);
		g_glob = 0;
	}
	free(oldval);
}

void	ft_cd_path(t_data *data, char *path)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(path, "cd"));
	if (chdir(path) == -1)
		return (print_error(path, "cd"));
	update_env_ifexist(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(path, "cd"));
	update_env_ifexist(data, "PWD", pwd);
}

// if HOME not set and path is ~, bash recreates the HOME path with
// the username
void	ft_cd_home(t_data *data, char *path)
{
	char	pwd[PATH_MAX];
	char	*home;

	home = getenv_value(data->env, "HOME");
	if (!home[0] && !path)
		return (print_error("HOME not set", "cd"));
	if (!home[0] && path)
		home = ft_strjoin("/Users/", getenv_value(data->env, "USER"));
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(home, "cd"));
	if (chdir(home) == -1)
		return (print_error(home, "cd"));
	update_env_ifexist(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(home, "cd"));
	update_env_ifexist(data, "PWD", pwd);
	free(home);
}

void	ft_cd_minus(t_data *data)
{
	char	pwd[PATH_MAX];
	char	*tmp;

	tmp = getenv_value(data->env, "OLDPWD");
	if (!tmp[0])
		return (print_error("OLDPWD not set", "cd"));
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(tmp, "cd"));
	if (chdir(tmp) == -1)
		return (print_error(tmp, "cd"));
	update_env_ifexist(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(tmp, "cd"));
	update_env_ifexist(data, "PWD", pwd);
	free(tmp);
}

int	ft_cd(t_data *data, char **args)
{
	char	*path;

	path = args[1];
	if (path && args[2])
	{
		g_glob = 1;
		print_error("too many arguments", "cd");
		return (0);
	}
	if (!path || ft_strncmp(path, "~", 2) == 0)
	{
		ft_cd_home(data, path);
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		ft_cd_minus(data);
	}
	else
		ft_cd_path(data, path);
	return (0);
}

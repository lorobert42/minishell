/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:11:34 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 13:56:43 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_ifexist(t_data *data, char *key, char *path)
{
	char	*oldval;
	char	*newval;

	oldval = ft_getenv(data->env, key);
	if (oldval)
	{
		newval = create_env_value(key, path);
		update_env(data, key, newval);
		g_glob.error = 0;
		free(oldval);
		free(newval);
	}
}

void	ft_cd_path(t_data *data, char *path)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(NULL, "cd"));
	if (chdir(path) == -1)
		return (print_error(NULL, path));
	update_env_ifexist(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(NULL, "cd"));
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
	{
		g_glob.error = 1;
		return (print_error("HOME not set", "cd"));
	}
	if (!home[0] && path)
		home = ft_strjoin("/Users/", getenv_value(data->env, "USER"));
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(NULL, "cd"));
	if (chdir(home) == -1)
		return (print_error(NULL, home));
	update_env_ifexist(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(NULL, "cd"));
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
		return (print_error(NULL, "cd"));
	if (chdir(tmp) == -1)
		return (print_error(NULL, tmp));
	update_env_ifexist(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_error(NULL, "cd"));
	update_env_ifexist(data, "PWD", pwd);
	free(tmp);
}

int	ft_cd(t_data *data, char **args)
{
	char	*path;

	path = args[1];
	if (!path)
	{
		ft_cd_home(data, path);
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		ft_cd_minus(data);
	}
	else
		ft_cd_path(data, path);
	if (errno != 0)
		g_glob.error = 1;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:11:34 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/31 15:17:52 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_cd_error(char *s)
{
	char	*error;

	g_glob = 1;
	error = ft_strjoin("cd: ", s);
	perror(error);
	free(error);
}

void	ft_cd_path(t_data *data, char *path)
{
	char	pwd[PATH_MAX];
	char	*envval;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_cd_error(path));
	if (chdir(path) == -1)
		print_cd_error(path);
	envval = ft_getenv(data->env, "OLDPWD");
	if (envval)
		ft_export(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		print_cd_error(path);
	envval = ft_getenv(data->env, "PWD");
	if (envval)
		ft_export(data, "PWD", pwd);
}

void	ft_cd_home(t_data *data)
{
	char	pwd[PATH_MAX];
	char	*home;
	char	*envval;

	home = getenv_value(data->env, "HOME");
	if (!home[0])
		return (print_cd_error("HOME not set"));
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (print_cd_error(home));
	if (chdir(home) == -1)
		print_cd_error(home);
	envval = ft_getenv(data->env, "OLDPWD");
	if (envval)
		ft_export(data, "OLDPWD", pwd);
	if (getcwd(pwd, PATH_MAX) == NULL)
		print_cd_error(home);
	envval = ft_getenv(data->env, "PWD");
	if (envval)
		ft_export(data, "PWD", pwd);
}

int	ft_cd(t_data *data, char *path)
{
	if (path == NULL)
	{
		ft_printf("cd with no argument\n");
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		ft_printf("cd -\n");
	}
	else if (ft_strncmp(path, "~", 2) == 0)
	{
		ft_cd_home(data);
	}
	else
		ft_cd_path(data, path);
	return (0);
}

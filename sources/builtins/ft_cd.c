/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:11:34 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/30 16:15:23 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*construct(char **dir, int size, char *res, int i)
{
	char	*old;

	old = ft_strdup(res);
	free(res);
	res = ft_strjoin(old, dir[i]);
	free(old);
	if (i != size - 1)
	{
		old = ft_strdup(res);
		free(res);
		res = ft_strjoin(old, "/");
		free(old);
	}
	return (res);
}

void	go_back(t_data * data)
{
	char	**dir;
	char	*res;
	char	*old;
	int		size;
	int		i;

	dir = ft_split(ft_getenv(data->env, "PWD"), '/');
	size = get_tab_size(dir) - 1;
	i = 0;
	res = malloc(0);
	while (i < size)
	{
		res = construct(dir, size, res, i);
		i++;
	}
	old = ft_strdup(res);
	ft_export(data, "OLDPWD", ft_getenv(data->env, "PWD"));
	free(res);
	res = ft_strjoin("/", old);
	free(old);
	ft_export(data, "PWD", res);
	free(res);
	clear_split(dir);
}

char	*get_pwd(char **env, int mode, char *path)
{
	char	*old;
	char	*res;
	char	*pwd;

	res = NULL;
	pwd = NULL;
	if (mode == 0)
	{
		pwd = getenv_value(env, "PWD");
		if (ft_strlen(pwd) > 1)
			old = ft_strjoin(pwd, "/");
		else
			old = ft_strdup("/");
		res = ft_strjoin(old, path);
		free(old);
	}
	return (res);
}

void	set_pwd(t_data *data, char *path, char *npath)
{
	if (path[0] == '/')
		npath = ft_strdup(path);
	else
		npath = get_pwd(data->env, 0, path);
	ft_printf("%s\n", npath);
	if (chdir(npath) != 0)
		ft_printf("Hérishell: cd: No such file or directory\n");
	else
	{
		ft_export(data, "OLDPWD", ft_getenv(data->env, "PWD"));
		ft_export(data, "PWD", npath);
	}
	free(npath);
}

int	ft_cd(t_data *data, char *path)
{
	char	*npath;
	char	*temp;

	npath = NULL;
	if (!path || ft_strncmp(path, "~", 1) == 0)
	{
		ft_export(data, "OLDPWD", ft_getenv(data->env, "PWD"));
		ft_export(data, "PWD", ft_getenv(data->env, "HOME"));
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		temp = ft_strdup(ft_getenv(data->env, "PWD"));
		ft_export(data, "PWD", ft_getenv(data->env, "OLDPWD"));
		ft_export(data, "OLDPWD", temp);
		free(temp);
	}
	else if (ft_strncmp(path, "..\0", 3) == 0)
		go_back(data);
	else
	{
		set_pwd(data, path, npath);
		free(npath);
	}
	return (0);
}

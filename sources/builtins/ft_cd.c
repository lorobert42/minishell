/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:11:34 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/28 14:16:40 by lorobert         ###   ########.fr       */
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

void	go_back(t_env *env)
{
	char	**dir;
	char	*res;
	char	*old;
	int		size;
	int		i;

	dir = ft_split(ft_getenv(env, "PWD"), '/');
	size = get_tab_size(dir) - 1;
	i = 0;
	res = malloc(0);
	while (i < size)
	{
		res = construct(dir, size, res, i);
		i++;
	}
	old = ft_strdup(res);
	ft_export(&env, "OLDPWD", ft_getenv(env, "PWD"));
	free(res);
	res = ft_strjoin("/", old);
	free(old);
	ft_export(&env, "PWD", res);
	free(res);
	clear_split(dir);
}

char	*get_pwd(t_env *env, int mode, char *path)
{
	char	*old;
	char	*res;
	char	*pwd;

	res = NULL;
	pwd = NULL;
	if (mode == 0)
	{
		pwd = ft_getenv(env, "PWD");
		if (ft_strlen(pwd) > 1)
			old = ft_strjoin(pwd, "/");
		else
			old = ft_strdup("/");
		res = ft_strjoin(old, path);
		free(old);
	}
	return (res);
}

void	set_pwd(char *path, char *npath, t_env *env)
{
	if (path[0] == '/')
		npath = ft_strdup(path);
	else
		npath = get_pwd(env, 0, path);
	if (chdir(npath) != 0)
		ft_printf("Hérishell: cd: No such file or directory\n");
	else
	{
		ft_export(&env, "OLDPWD", ft_getenv(env, "PWD"));
		ft_export(&env, "PWD", npath);
	}
	free(npath);
}

int	ft_cd(char *path, t_env **env)
{
	char	*npath;
	char	*temp;

	npath = NULL;
	if (!path || ft_strncmp(path, "~", 1) == 0)
	{
		ft_export(env, "OLDPWD", ft_getenv(*env, "PWD"));
		ft_export(env, "PWD", ft_getenv(*env, "HOME"));
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		temp = ft_strdup(ft_getenv(*env, "PWD"));
		ft_export(env, "PWD", ft_getenv(*env, "OLDPWD"));
		ft_export(env, "OLDPWD", temp);
		free(temp);
	}
	else if (ft_strncmp(path, "..\0", 3) == 0)
		go_back(*env);
	else
	{
		set_pwd(path, npath, *env);
		free(npath);
	}
	return (0);
}

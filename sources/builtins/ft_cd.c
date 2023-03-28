/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:11:34 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/24 11:40:14 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Change the current working directory to path.
Change OLDPWD to the previous PWD.
*/
int	ft_cd(char *path, t_env **env)
{
	char	old_cwd[PATH_MAX];
	char	cwd[PATH_MAX];
	t_env	*tmp_path;

	getcwd(old_cwd, PATH_MAX);
	if (chdir(path) != 0)
		return (1);
	getcwd(cwd, PATH_MAX);
	tmp_path = create_entry("PWD", cwd);
	ft_export(env, tmp_path);
	tmp_path = create_entry("OLDPWD", old_cwd);
	ft_export(env, tmp_path);
	return (0);
}

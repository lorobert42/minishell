/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:33:27 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 12:41:04 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Print current working directory.
*/
int	ft_pwd(char **env)
{
	char	var[PATH_MAX];
	char	*envvar;

	if (getcwd(var, PATH_MAX) != NULL)
	{
		ft_printf("%s\n", var);
		g_glob.error = 0;
	}
	else
	{
		envvar = getenv_value(env, "PWD");
		ft_printf("%s\n", envvar);
		free(envvar);
	}
	return (0);
}

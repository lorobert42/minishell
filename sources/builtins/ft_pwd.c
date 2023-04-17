/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:33:27 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/17 16:17:12 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Print current working directory.
*/
int	ft_pwd(void)
{
	char	var[PATH_MAX];

	if (getcwd(var, PATH_MAX) != NULL)
	{
		ft_printf("%s\n", var);
		g_glob = 0;
	}
	else
	{
		print_error(NULL, "PWD");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:33:27 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/31 14:43:20 by lorobert         ###   ########.fr       */
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
		ft_printf("%s\n", var);
	else
	{
		g_glob = 1;
		perror("pwd");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:33:27 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/15 16:55:03 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env, int fd)
{
	char	cwd[PATH_MAX];

	(void)env;
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, fd);
		return (0);
	}
	return (1);
}

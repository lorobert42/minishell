/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:33:27 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/11 18:25:48 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

int	ft_pwd(char **env, int fd)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:15:27 by afavre            #+#    #+#             */
/*   Updated: 2023/05/05 14:59:44 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**set_value(char **res, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i] != '=')
	{
		res[0][i] = arg[i];
		i++;
	}
	res[0][i] = '\0';
	i++;
	while (arg[i] != '\0')
	{
		res[1][j] = arg[i];
		j++;
		i++;
	}
	res[1][j] = '\0';
	res[2] = NULL;
	return (res);
}

char	**set_export_option(char *arg)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * 3);
	while (arg[i] != '=')
		i++;
	res[0] = malloc(sizeof(char) * (i + 1));
	i++;
	while (arg[i] != '\0')
	{
		j++;
		i++;
	}
	res[1] = malloc(sizeof(char) * (j + 1));
	return (set_value(res, arg));
}

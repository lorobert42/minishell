/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:27:20 by afavre            #+#    #+#             */
/*   Updated: 2023/04/26 11:35:50 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *path, char *cmd)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (cmd == NULL)
		res = ft_strdup(temp);
	else
		res = ft_strjoin(temp, cmd);
	free(temp);
	return (res);
}

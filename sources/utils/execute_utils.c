/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:27:20 by afavre            #+#    #+#             */
/*   Updated: 2023/03/30 13:27:24 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *path, char *cmd)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	res = ft_strjoin(temp, cmd);
	free(temp);
	return (res);
}

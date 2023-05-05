/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:15:27 by afavre            #+#    #+#             */
/*   Updated: 2023/05/05 11:15:30 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**set_export_option(char *arg)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * 2);
	while (arg[i] != '=')
		i++;
	return (NULL);
}

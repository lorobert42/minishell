/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:57:23 by afavre            #+#    #+#             */
/*   Updated: 2023/03/28 16:57:25 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_full_env(t_env *env, char *key)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(key, "=");
	res = ft_strjoin(temp, ft_getenv(env, key));
	free(temp);
	ft_printf("test -> res");
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:57:45 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/16 10:07:08 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env **env, char *s)
{
	t_env	*prev;
	t_env	*to_del;

	to_del = *env;
	if (ft_strncmp(to_del->key, s, ft_strlen(s) + 1) == 0)
	{
		*env = (*env)->next;
		return (0);
	}
	prev = to_del;
	to_del = to_del->next;
	while (to_del)
	{
		if (ft_strncmp(to_del->key, s, ft_strlen(s) + 1) == 0)
		{
			prev->next = to_del->next;
			return (0);
		}
		prev = to_del;
		to_del = to_del->next;
	}
	return (0);
}

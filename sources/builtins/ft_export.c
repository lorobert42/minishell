/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:11:25 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/16 13:38:34 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Set a new environment variable, if key already exists, replace it by the new
one.
*/
// TODO: Norm
int	ft_export(t_env **env, char *s)
{
	t_env	*new;
	t_env	*prev;
	t_env	*next;

	new = extract_entry(s);
	prev = *env;
	if (ft_strncmp(prev->key, new->key, ft_strlen(prev->key) + 1) == 0)
	{
		new->next = prev->next;
		*env = new;
		return (0);
	}
	next = prev->next;
	while (next)
	{
		if (ft_strncmp(next->key, new->key, ft_strlen(new->key) + 1) == 0)
		{
			new->next = next->next;
			prev->next = new;
			return (0);
		}
		prev = next;
		next = next->next;
	}
	prev->next = new;
	return (0);
}

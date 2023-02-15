/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:11:25 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/15 16:54:59 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_printf("Last entry: %s=%s\n", next->key, next->value);
	prev->next = new;
	return (0);
}

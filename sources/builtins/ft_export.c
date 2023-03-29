/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:11:25 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/28 14:23:31 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Set a new environment variable, if key already exists, replace it by the new
one.
*/
int	check_export_format(char *args)
{
	int res;
	int i;

	res = 1;
	i = 1;
	if (ft_isalpha(args[0]) != 0 || args[0] == '_')
		res = 0;
	while (args[i])
	{
		if (args[i] == ' ' || args[i] == '!' || args[i] == '*' || args[i] == '%')
			res = 1;
		if (ft_isalnum(args[i]) == 0)
		{
			if (args[i] != '_')
				res = 1;
		}
		i++;
	}
	return(res);
}

int	update_first(t_env **env, t_env *new, t_env *prev)
{
	new->next = prev->next;
	del_env(*env);
	*env = new;
	return (0);
}

int	update_not_first(t_env *new, t_env *next, t_env *prev)
{
	new->next = next->next;
	del_env(next);
	prev->next = new;
	return (0);
}

int	ft_export(t_env **env, char *key, char *value)
{
	t_env	*prev;
	t_env	*next;
	t_env	*new;

	if (!check_export_format(key))
	{
		prev = *env;
		new = create_entry(key, value);
		if (ft_strncmp(prev->key, new->key, ft_strlen(prev->key) + 1) == 0)
			return (update_first(env, new, prev));
		next = prev->next;
		while (next)
		{
			if (ft_strncmp(next->key, new->key, ft_strlen(new->key) + 1) == 0)
				return (update_not_first(new, next, prev));
			prev = next;
			next = next->next;
		}
		prev->next = new;
	}
	return (0);
}

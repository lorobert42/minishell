/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:12:59 by lorobert          #+#    #+#             */
/*   Updated: 2023/02/24 09:36:40 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Transform char * containing environment variable, to env struct.
*/
t_env	*extract_entry(char *env_entry)
{
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	i = ft_strchr(env_entry, '=') - env_entry;
	new->key = ft_substr(env_entry, 0, i);
	new->value = ft_substr(env_entry, i + 1, ft_strlen(env_entry) - i - 1);
	new->next = NULL;
	return (new);
}

/*
Create a new env entry from two strings.
*/
t_env	*create_entry(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

/*
Transforms char ** containing environment variables, to chained env structs.
*/
char	**parse_env(char **env_strs)
{
	char	**env;
	int 	tab_size;

	env = NULL;
	tab_size = get_tab_size(env_strs);
	ft_printf("tab size ----> %d\n");
	return (env);
}

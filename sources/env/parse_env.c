/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:12:59 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/04 09:25:07 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**parse_env(char **env_strs)
{
	char	**env;
	int		tab_size;
	int		i;

	env = NULL;
	i = 0;
	tab_size = get_tab_size(env_strs);
	env = malloc(sizeof(char *) * (tab_size + 1));
	if (!env)
		fatal_error(NULL, "malloc", 1);
	while (i < tab_size)
	{
		env[i] = ft_strdup(env_strs[i]);
		i++;
	}
	env[tab_size] = NULL;
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:57:45 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 11:33:48 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**remove_string(char **env, int i)
{
	int		size;
	int		j;
	char	**new;

	size = get_tab_size(env);
	new = malloc(sizeof(char *) * size);
	if (!new)
		fatal_error(NULL, "malloc", 1);
	j = 0;
	while (j < i)
	{
		new[j] = ft_strdup(env[j]);
		j++;
	}
	while (j < size - 1)
	{
		new[j] = ft_strdup(env[j + 1]);
		j++;
	}
	new[j] = NULL;
	clear_split(env);
	return (new);
}

/*
Remove environment variable, if key does not exists, do nothing.
*/
int	ft_unset(t_data *data, char **arg)
{
	int		i;
	int		j;

	j = 0;
	while (arg[++j])
	{
		if (!is_valid_key(arg[j]))
		{
			print_error("not a valid identifier", "unset");
			g_glob.error = 1;
			continue ;
		}
		i = -1;
		while (data->env[++i])
		{
			if (ft_strncmp(data->env[i], arg[j], ft_strchr(data->env[i], '=') \
			- data->env[i]) == 0)
			{
				g_glob.error = 0;
				data->env = remove_string(data->env, i);
				break ;
			}
		}
	}
	return (0);
}

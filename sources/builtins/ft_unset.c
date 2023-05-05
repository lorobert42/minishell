/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:57:45 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 10:15:27 by lorobert         ###   ########.fr       */
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
int	ft_unset(t_data *data, char *s)
{
	int		i;

	if (s != NULL)
	{
		if (!is_valid_key(s))
		{
			errno = EINVAL;
			print_error("not a valid identifier", "unset");
			g_glob.error = 1;
			return (0);
		}
		i = 0;
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], s, ft_strchr(data->env[i], '=') \
			- data->env[i]) == 0)
			{
				g_glob.error = 0;
				data->env = remove_string(data->env, i);
				return (0);
			}
			i++;
		}
	}
	return (0);
}

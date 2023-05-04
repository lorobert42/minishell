/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:07:11 by afavre            #+#    #+#             */
/*   Updated: 2023/05/04 10:52:57 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	**tab_add_new(t_data *data, char *content)
{
	int		size;
	int		i;
	char	**new;

	i = 0;
	size = get_tab_size(data->env);
	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		fatal_error(NULL, "malloc", 1);
	while (i < size)
	{
		new[i] = ft_strdup(data->env[i]);
		i++;
	}
	new[i] = ft_strdup(content);
	new[i + 1] = NULL;
	return (new);
}

char	**tab_add_back(t_data *data, char *content)
{
	char	**new;

	if (data->env != NULL)
	{
		new = tab_add_new(data, content);
	}
	else
	{
		new = malloc(sizeof(char *) * 2);
		if (!new)
			fatal_error(NULL, "malloc", 1);
		new[0] = ft_strdup(content);
		new[1] = NULL;
	}
	clear_split(data->env);
	return (new);
}

void	swap_somthing(char **env, int i, int *swapped)
{
	char	*temp;

	temp = env[i];
	env[i] = env[i + 1];
	env[i + 1] = temp;
	*swapped = 1;
}

char	**sort_tab(char **env)
{
	int		i;
	int		num_env;
	int		swapped;

	num_env = 0;
	while (env[num_env])
		num_env++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < num_env - 1)
		{
			if (strcmp(env[i], env[i + 1]) > 0)
			{
				swap_somthing(env, i, &swapped);
			}
			i++;
		}
	}
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:07:11 by afavre            #+#    #+#             */
/*   Updated: 2023/03/28 11:28:52 by lorobert         ###   ########.fr       */
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

void	print_str_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

char	**tab_add_back(t_data *data, char *content)
{
	int		size;
	int		i;
	char	**new;

	i = 0;
	if (data->env != NULL)
	{
		size = get_tab_size(data->env);
		new = malloc(sizeof(char *) * (size + 2));
		while (i < size)
		{
			new[i] = ft_strdup(data->env[i]);
			i++;
		}
		new[i] = ft_strdup(content);
		new[i + 1] = NULL;
	}
	else
	{
		new = malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(content);
		new[1] = NULL;
	}
	clear_split(data->env);
	return (new);
}

char	**sort_tab(char **env)
{
	int		i;
	int		num_env;
	char	*temp;

	num_env = 0;
	while (env[num_env]) {
		num_env++;
	}

	int swapped = 1;
	while (swapped) {
		swapped = 0;
		i = 0;
		while (i < num_env - 1) {
			if (strcmp(env[i], env[i+1]) > 0) {
				temp = env[i];
				env[i] = env[i+1];
				env[i+1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
	return (env);
}

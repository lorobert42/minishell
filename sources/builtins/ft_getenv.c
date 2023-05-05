/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:17:47 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 12:42:56 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*getenv_value(char **env, char *key)
{
	char	*value;
	char	**tmp;

	value = ft_getenv(env, key);
	if (!value)
		return (ft_strdup(""));
	tmp = set_export_option(value);
	free(value);
	if (!tmp[1])
	{
		clear_split(tmp);
		return (ft_strdup(""));
	}
	value = ft_strdup(tmp[1]);
	clear_split(tmp);
	return (value);
}

/*
Returns the value of env variable key, or NULL if not existant
*/
int	get_env_index(char **env, char *key)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strchr(env[i], '=') - env[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char **env, char *key)
{
	int		i;
	char	*envkey;

	i = 0;
	while (env[i])
	{
		envkey = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (ft_strncmp(envkey, key, ft_strlen(key) + 1) == 0)
		{
			free(envkey);
			return (ft_strdup(env[i]));
		}
		free(envkey);
		i++;
	}
	return (NULL);
}

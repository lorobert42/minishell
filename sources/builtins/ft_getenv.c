/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:17:47 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/03 13:57:35 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenv_value(char **env, char *key)
{
	char	*value;
	char	**tmp;

	value = ft_getenv(env, key);
	if (!value)
		return (ft_strdup(""));
	tmp = ft_split(value, '=');
	free(value);
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

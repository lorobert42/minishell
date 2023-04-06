/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:11:25 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/31 14:07:01 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Set a new environment variable, if key already exists, replace it by the new
one.
*/
int	check_export_format(char *args)
{
	int	res;
	int	i;

	res = 1;
	i = 1;
	if (ft_isalpha(args[0]) != 0 || args[0] == '_')
		res = 0;
	while (args[i])
	{
		if (args[i] == ' ' || args[i] == '!' || args[i] == '*' || \
			args[i] == '%')
			res = 1;
		if (ft_isalnum(args[i]) == 0)
		{
			if (args[i] != '_')
				res = 1;
		}
		i++;
	}
	return (res);
}

char	*create_env_value(char *key, char *value)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(key, "=");
	if (!value)
		res = ft_strdup(temp);
	else
		res = ft_strjoin(temp, value);
	free(temp);
	return (res);
}

int		print_export(char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		sub = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i] + 1);
		ft_printf("declare -x %s\"", sub);
		j = ft_strlen(sub);
		free(sub);
		while (env[i][j])
		{
			if (env[i][j] == '"' && env[i][j - 1] != '\\')
				ft_printf("\\");
			else if (env[i][j] == '\\')
				ft_printf("\\\\");
			ft_printf("%c", env[i][j]);
			j++;
		}
		ft_printf("\"\n");
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, char *key, char *value)
{
	char	*new_value;
	int		index;
	int		res;

	if (!key)
	{
		print_export(data->env);
		return (0);
	}
	new_value = create_env_value(key, value);
	res = check_export_format(key);
	if (res == 0)
	{
		if (ft_getenv(data->env, key) != NULL)
		{
			index = get_env_index(data->env, key);
			free(data->env[index]);
			data->env[index] = ft_strdup(new_value);
		}
		else
			data->env = tab_add_back(data, new_value);
	}
	free(new_value);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:11:25 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 11:56:51 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_key(char *args)
{
	int	i;

	if (args == NULL)
		return (0);
	i = 1;
	if (ft_isalpha(args[0]) == 0 && args[0] != '_')
		return (0);
	while (ft_isalnum(args[i]) != 0 || args[i] == '_')
		i++;
	if (args[i] != '\0')
		return (0);
	return (1);
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

int	print_export(char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	env = sort_tab(env);
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
	return (0);
}

void	update_env(t_data *data, char *key, char *new_value)
{
	char	*env;
	int		index;
	char	**split;

	env = ft_getenv(data->env, key);
	if (env != NULL)
	{
		index = get_env_index(data->env, key);
		free(data->env[index]);
		split = set_export_option(new_value);
		data->env[index] = create_env_value(key, split[1]);
		clear_split(split);
		g_glob.error = 0;
	}
	else
	{
		data->env = tab_add_back(data, new_value);
		g_glob.error = 0;
	}
	free(env);
}

int	ft_export(t_data *data, char **arg)
{
	char	*equal;
	char	*key;
	int		res;
	int		i;

	i = 0;
	while (arg[++i])
	{
		equal = ft_strchr(arg[i], '=');
		if (!equal)
			key = ft_strdup(arg[i]);
		else
			key = ft_substr(arg[i], 0, equal - arg[i]);
		res = is_valid_key(key);
		if (res == 1 && ft_strchr(arg[i], '=') != NULL)
			update_env(data, key, arg[i]);
		else if (res == 0)
		{
			g_glob.error = 1;
			print_error("not a valid identifier", "export");
		}
		free(key);
	}
	return (0);
}

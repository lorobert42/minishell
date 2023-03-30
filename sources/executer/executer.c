/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/03/30 15:59:27 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(t_data *data)
{
	char	**path;
	int		i;

	path = ft_split(ft_getenv(data->env, "PATH"), ':');
	i = 0;
	while (path[i] != NULL)
	{
		if (access(get_path(path[i], data->table->commands->args[0]), F_OK | R_OK) == 0)
			return (get_path(path[i], data->table->commands->args[0]));
		i++;
	}
	clear_split(path);
	return ("NULL");
}

int	executer(t_data *data)
{
	int	id;
	int	res;

	id = fork();
	if (id == 0)
	{
		ft_printf("path -----> %s\n", find_path(data));
		execve(find_path(data), data->table->commands->args, data->env);
		exit(0);
	}

	else
	{
		waitpid(id, &res, 0);
	}
	return (0);
}

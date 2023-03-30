/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/03/30 12:04:48 by afavre           ###   ########.fr       */
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
		if (access(get_path(path[i], data->table.commands->command[0]), F_OK | R_OK) == 0)
			return (get_path(path[i], data->table.commands->command[0]));
		i++;
	}
	clear_split(path);
	return ("NULL");
}

int	executer(t_data *data)
{
	(void)data;
	int id;
	int res;

	id = fork();
	if (id == 0)
	{
		ft_printf("path -----> %s\n", find_path(data));
		execve(find_path(data), data->table.commands->command, data->env);
		exit(0);
	}

	else
	{
		waitpid(id, &res, 0);
	}
	return (0);
}

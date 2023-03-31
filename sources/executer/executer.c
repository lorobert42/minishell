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
	return (NULL);
}

/*int	executer(t_data *data)
{
	int i;

	i = 0;
	while (i < data->table->n_commands)
	{
		ft_printf("%s\n", data->table->commands->args[0]);
		i++;
	}
	return (0);
}*/

int	executer(t_data *data)
{
	int		id;
	char	*path;
	int		i;

	i =0;
	while (i < data->table->n_commands)
	{
		pipe(data->fd);
		id = fork();
		if (id == 0)
		{
			path = find_path(data);
			if (path != NULL)
			{
				close(data->fd[0]);
				dup2(data->fd[1], STDOUT_FILENO);
				close(data->fd[1]);
				execve(path, data->table->commands->args, data->env);
			}
			else
			{
				ft_printf("🤷 Hérishell: %s: a pas trouver ... 🤷\n", data->table->commands->args[0]);
				exit(0);
			}
		}
		else
		{
			waitpid(id, &g_glob, 0);
			close(data->fd[1]);
			char buffer[1024];
			int count;
			while ((count = read(data->fd[0], buffer, sizeof(buffer))) > 0)
			{
				write(STDOUT_FILENO, buffer, count);
			}
			close(data->fd[0]);
		}
		i++;
	}
	return (0);
}


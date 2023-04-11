/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/04/06 15:36:56 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(t_data *data, int num)
{
	char	*env;
	char	**path;
	int		i;

	env = ft_getenv(data->env, "PATH");
	if (env != NULL)
	{
		path = ft_split(env, ':');
		i = 0;
		while (path[i] != NULL)
		{
			if (access(get_path(path[i], data->table->commands[num].args[0]), \
		F_OK | R_OK) == 0)
				return (get_path(path[i], data->table->commands[num].args[0]));
			i++;
		}
		clear_split(path);
	}
	return (NULL);
}

void	children(t_data *data, int *prev_read, int i)
{
	char	*path;

	close(data->fd[0]);
	if (data->table->commands[i].infile && data->table->commands[i].append)
		dup2(data->table->commands[i].fd[0], STDIN_FILENO);
	else if (data->table->commands[i].infile)
	{
		data->table->commands[i].fd[0] = open(data->table->commands[i].infile, O_RDONLY);
		dup2(data->table->commands[i].fd[0], STDIN_FILENO);
	}
	else
		dup2(*prev_read, STDIN_FILENO);
	if (data->table->commands[i].outfile && data->table->commands[i].append)
	{
		data->table->commands[i].fd[1] = open(data->table->commands[i].outfile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH);
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
	}
	else if (data->table->commands[i].outfile)
	{
		data->table->commands[i].fd[1] = open(data->table->commands[i].outfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH);
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
	}
	else if (i < data->table->n_commands - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (check_builtins_forks(data, i) == 1)
	{
		path = find_path(data, i);
		if (path != NULL)
		{
			execve(path, data->table->commands[i].args, data->env);
		}
		else
		{
			ft_printf("🤷 Hérishell: %s: a pas trouver ... 🤷\n", \
				data->table->commands->args[0]);
		}
	}
	exit(0);
}

void	execution_loop(t_data *data)
{
	int		prev_read;
	pid_t	id;
	int		i;

	i = 0;
	prev_read = 0;
	while (i < data->table->n_commands)
	{
		pipe(data->fd);
		if (!check_builtins_out(data, i))
		{
			i++;
			continue ;
		}
		id = fork();
		if (id == 0)
			children(data, &prev_read, i);
		else
		{
			waitpid(id, &g_glob, 0);
			close(data->fd[1]);
			prev_read = data->fd[0];
		}
		i++;
	}
}
int	execute(t_data *data)
{
	set_heredoc(data);
	execution_loop(data);
	return (0);
}

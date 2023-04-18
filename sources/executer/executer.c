/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/04/17 16:54:07 by lorobert         ###   ########.fr       */
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

void	redirection(t_data *data, int i, int *prev_read)
{
	if (data->table->commands[i].infile && data->table->commands[i].append)
		dup2(data->table->commands[i].fd[0], STDIN_FILENO);
	else if (data->table->commands[i].infile)
	{
		data->table->commands[i].fd[0] = open(data->table->commands[i].infile, \
			O_RDONLY);
		dup2(data->table->commands[i].fd[0], STDIN_FILENO);
	}
	else
		dup2(*prev_read, STDIN_FILENO);
	if (data->table->commands[i].outfile && data->table->commands[i].append)
	{
		data->table->commands[i].fd[1] = open(data->table->commands[i].outfile, \
		O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
	}
	else if (data->table->commands[i].outfile)
	{
		data->table->commands[i].fd[1] = open(data->table->commands[i].outfile, \
			O_WRONLY | O_CREAT, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
	}
	else if (i < data->table->n_commands - 1)
		dup2(data->fd[1], STDOUT_FILENO);
}

void	children(t_data *data, int *prev_read, int i)
{
	char	*path;

	close(data->fd[0]);
	redirection(data, i, prev_read);
	if (check_builtins_forks(data, i) == 1)
	{
		path = find_path(data, i);
		if (path != NULL)
			execve(path, data->table->commands[i].args, data->env);
		else
			ft_printf("🤷 Hérishell: %s: a pas trouver ... 🤷\n", \
				data->table->commands[i].args[0]);
	}
	exit(0);
}

void	execution_loop(t_data *data)
{
	int		prev_read;
	pid_t	id;
	int		i;
	int		status;
	int		wait;

	i = 0;
	prev_read = 0;
	while (i < data->table->n_commands)
	{
		if (data->table->commands[i].args[0] && ft_strncmp(data->table->commands[i].args[0], "cat\0", 4) == 0)
		{
			termios_restore_ctrl();
			g_glob[1] = 43;
			//ft_printf("BEFORE -> %d\n", data->sig_state);
		}
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
			close(data->fd[1]);
			prev_read = data->fd[0];
		}
		i++;
	}
	wait = waitpid(-1, &status, 0);
	termios_remove_ctrl();
	while (wait != -1)
	{
		if (wait == id)
			g_glob[0] = status;
		wait = waitpid(-1, &status, 0);
	}
}

int	execute(t_data *data)
{
	set_heredoc(data);
	execution_loop(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/04/20 14:23:03 by lorobert         ###   ########.fr       */
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

void	redirection_out(t_data *data, int i, int solo)
{
	t_file	*current;
	t_file	*prev;

	current = data->table->commands[i].outfiles;
	if (!current && !solo)
		dup2(data->fd[1], STDOUT_FILENO);
	prev = NULL;
	while (current)
	{
		if (prev)
			close(data->table->commands[i].fd[1]);
		if (current->append)
		{
			data->table->commands[i].fd[1] = open(current->name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		}
		else
		{
			data->table->commands[i].fd[1] = open(current->name, \
			O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		}
		prev = current;
		current = current->next;
	}
}

void	redirection_in(t_data *data, int i, int *prev_read)
{
	t_file	*current;
	t_file	*prev;

	current = data->table->commands[i].infiles;
	if (!current && prev_read)
		dup2(*prev_read, STDIN_FILENO);
	prev = NULL;
	while (current)
	{
		if (prev)
			close(data->table->commands[i].fd[0]);
		if (current->append)
			dup2(data->table->commands[i].fd[0], STDIN_FILENO);
		else
		{
			data->table->commands[i].fd[0] = open(current->name, \
				O_RDONLY);
			dup2(data->table->commands[i].fd[0], STDIN_FILENO);
		}
		prev = current;
		current = current->next;
	}
}

void	children(t_data *data, int *prev_read, int i)
{
	char	*path;

	close(data->fd[0]);
	redirection_in(data, i, prev_read);
	redirection_out(data, i, 0);
	if (check_builtins(data, data->table->commands[i].args) == 1)
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

	i = 0;
	prev_read = 0;
	while (i < data->table->n_commands)
	{
		pipe(data->fd);
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
	while (waitpid(-1, &status, 0) > 0)
	{
	}
	if (WIFEXITED(status))
		g_glob.error = WEXITSTATUS(status);
}

int	execute(t_data *data)
{
	int	saved_io[2];

	set_heredoc(data);
	if (data->table->n_commands == 1)
	{
		saved_io[0] = dup(STDIN_FILENO);
		saved_io[1] = dup(STDOUT_FILENO);
		redirection_in(data, 0, NULL);
		redirection_out(data, 0, 1);
		if (check_builtins(data, data->table->commands[0].args) == 0)
		{
			if (data->table->commands[0].outfiles)
			{
				dup2(saved_io[1], STDOUT_FILENO);
				close(data->table->commands[0].fd[1]);
			}
			else if (data->table->commands[0].infiles)
			{
				dup2(saved_io[0], STDIN_FILENO);
				close(data->table->commands[0].fd[0]);
			}
			return (0);
		}
	}
	execution_loop(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:15:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/26 10:58:17 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipe(t_data *data, int i)
{
	if (close(data->table->commands[i].fd[0]) == -1)
		print_error(NULL, "closing pipe 0");
	if (close(data->table->commands[i].fd[1]) == -1)
		print_error(NULL, "closing pipe 1");
}

int	redir_pipe(t_data *data, int i)
{
	if (i > 0 && !data->table->commands[i].infiles)
	{
		dup2(data->table->commands[i - 1].fd[0], STDIN_FILENO);
		close_pipe(data, i - 1);
	}
	if (i < data->table->n_commands - 1)
	{
		if (!data->table->commands[i].infiles)
		{
			if (close(data->table->commands[i].fd[0]) == -1)
				print_error(NULL, "close3");
		}
		if (!data->table->commands[i].outfiles)
		{
			dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
			if (close(data->table->commands[i].fd[1]) == -1)
				print_error(NULL, "close4");
		}
	}
	return (0);
}

int	redir_file_in(t_data *data, int i)
{
	t_file	*current;

	current = data->table->commands[i].infiles;
	if (current == NULL)
		return (0);
	while (current)
	{
		data->table->commands[i].fd[0] = open(current->name, O_RDONLY);
		if (data->table->commands[i].fd[0] == -1)
		{
			print_error(NULL, current->name);
			return (1);
		}
		current = current->next;
	}
	dup2(data->table->commands[i].fd[0], STDIN_FILENO);
	if (close(data->table->commands[i].fd[0]) == -1)
		print_error(NULL, "closing pipe infile");
	return (0);
}

int	redir_file_out(t_data *data, int i)
{
	t_file	*current;
	t_file	*prev;

	current = data->table->commands[i].outfiles;
	if (!current)
		return (0);
	prev = NULL;
	while (current)
	{
		if (prev)
			close(data->table->commands[i].fd[1]);
		if (current->append)
		{
			data->table->commands[i].fd[1] = open(current->name, O_WRONLY | \
				O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (data->table->commands[i].fd[1] == -1)
			{
				print_error(NULL, current->name);
				return (1);
			}
		}
		else
		{
			data->table->commands[i].fd[1] = open(current->name, O_WRONLY | \
				O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (data->table->commands[i].fd[1] == -1)
			{
				print_error(NULL, current->name);
				return (1);
			}
		}
		prev = current;
		current = current->next;
	}
	dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
	if (close(data->table->commands[i].fd[1]) == -1)
		print_error(NULL, "closing pipe outfile");
	return (0);
}

void	close_redirections(t_data *data, int i)
{
	if (data->table->commands[i].outfiles)
		close(data->table->commands[i].fd[1]);
	if (data->table->commands[i].infiles)
		close(data->table->commands[i].fd[0]);
}

void	restore_stdio(t_data *data)
{
	dup2(data->saved_io[0], STDIN_FILENO);
	close(data->saved_io[0]);
	dup2(data->saved_io[1], STDOUT_FILENO);
	close(data->saved_io[1]);
}

void	delete_heredoc(t_data *data, int i)
{
	t_file	*current;

	current = data->table->commands[i].infiles;
	while (current && current->next)
	{
		current = current->next;
	}
	if (current)
	{
		if (current->append)
		{
			if (unlink(current->name) == -1)
				print_error(NULL, "deleting heredoc");
		}
	}
}

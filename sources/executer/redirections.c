/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:15:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/21 12:51:19 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirection_in(t_data *data, int i)
{
	t_file	*current;
	t_file	*prev;

	current = data->table->commands[i].infiles;
	if (!current && i > 0)
	{
		dup2(data->table->commands[i - 1].fd[0], STDIN_FILENO);
		close(data->table->commands[i - 1].fd[0]);
		close(data->table->commands[i - 1].fd[1]);
	}
	if (!current && i < data->table->n_commands - 1)
	{
		close(data->table->commands[i].fd[0]);
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		close(data->table->commands[i].fd[1]);
	}
	prev = NULL;
	while (current)
	{
		if (prev)
		{
			close(data->table->commands[i].fd[0]);
			if (prev->append)
				unlink(prev->name);
		}
		data->table->commands[i].fd[0] = open(current->name, \
			O_RDONLY);
		if (data->table->commands[i].fd[0] == -1)
		{
			print_error(NULL, current->name);
			return (1);
		}
		dup2(data->table->commands[i].fd[0], STDIN_FILENO);
		prev = current;
		current = current->next;
	}
	return (0);
}

int	redirection_out(t_data *data, int i, int solo)
{
	t_file	*current;
	t_file	*prev;

	current = data->table->commands[i].outfiles;
	if (!current && !solo && i < data->table->n_commands - 1)
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
	prev = NULL;
	while (current)
	{
		if (prev)
			close(data->table->commands[i].fd[1]);
		if (current->append)
		{
			data->table->commands[i].fd[1] = open(current->name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (data->table->commands[i].fd[1] == -1)
			{
				print_error(NULL, current->name);
				return (1);
			}
			dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		}
		else
		{
			data->table->commands[i].fd[1] = open(current->name, \
			O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (data->table->commands[i].fd[1] == -1)
			{
				print_error(NULL, current->name);
				return (1);
			}
			dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	close_redirections(t_data *data, int i)
{
	t_file	*current;

	if (data->table->commands[i].outfiles)
		close(data->table->commands[i].fd[1]);
	current = data->table->commands[i].infiles;
	while (current && current->next)
	{
		if (current->append)
			unlink(current->name);
		current = current->next;
	}
	if (current)
	{
		close(data->table->commands[i].fd[0]);
		if (current->append)
			unlink(current->name);
	}
}

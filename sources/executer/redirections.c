/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:15:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/03 10:47:05 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redir_file_in(t_data *data, int i)
{
	t_file	*current;
	t_file	*prev;

	current = data->table->commands[i].infiles;
	if (current == NULL)
		return (0);
	prev = NULL;
	while (current)
	{
		if (prev)
			close(data->table->commands[i].fd_in);
		data->table->commands[i].fd_in = open(current->name, O_RDONLY);
		if (data->table->commands[i].fd_in == -1)
		{
			print_error(NULL, current->name);
			return (1);
		}
		current = current->next;
	}
	dup2(data->table->commands[i].fd_in, STDIN_FILENO);
	return (0);
}

int	create_file(t_data *data, t_file *prev, t_file *current, int i)
{
	if (prev)
		close(data->table->commands[i].fd_out);
	if (current->append)
	{
		data->table->commands[i].fd_out = open(current->name, O_WRONLY | \
				O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (data->table->commands[i].fd_out == -1)
		{
			print_error(NULL, current->name);
			return (1);
		}
	}
	else
	{
		data->table->commands[i].fd_out = open(current->name, O_WRONLY | \
				O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (data->table->commands[i].fd_out == -1)
		{
			print_error(NULL, current->name);
			return (1);
		}
	}
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
		if (create_file(data, prev, current, i) == 1)
			return (1);
		prev = current;
		current = current->next;
	}
	dup2(data->table->commands[i].fd_out, STDOUT_FILENO);
	return (0);
}

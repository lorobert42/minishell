/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:15:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/21 14:45:23 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirection_in(t_data *data, int i)
{
	t_file	*current;
	t_file	*prev;
	int		fd;

	current = data->table->commands[i].infiles;
	prev = NULL;
	while (current)
	{
		if (prev)
		{
			close(fd);
			if (prev->append)
				unlink(prev->name);
		}
		fd = open(current->name, O_RDONLY);
		if (fd == -1)
		{
			print_error(NULL, current->name);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	if (i > 0 && data->table->commands[i].infiles)
	{
		if (close(data->table->commands[i - 1].fd[0]) == -1)
			print_error(NULL, ft_strjoin(data->table->commands[i].args[0], " close0"));
		data->table->commands[i - 1].fd[0] = fd;
	}
	else if (i == 0 && data->table->commands[i].infiles)
	{
		dup2(data->table->commands[i].fd[0], STDIN_FILENO);
	}
	if (i > 0)
	{
		dup2(data->table->commands[i - 1].fd[0], STDIN_FILENO);
		if (close(data->table->commands[i - 1].fd[0]) == -1)
			print_error(NULL, ft_strjoin(data->table->commands[i].args[0], " close1"));
		if (close(data->table->commands[i - 1].fd[1]) == -1)
			print_error(NULL, ft_strjoin(data->table->commands[i].args[0], " close2"));
	}
	return (0);
}

int	redirection_out(t_data *data, int i, int solo)
{
	t_file	*current;
	t_file	*prev;
	int		fd;

	(void)solo;
	current = data->table->commands[i].outfiles;
	prev = NULL;
	while (current)
	{
		if (prev)
			close(fd);
		if (current->append)
		{
			fd = open(current->name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (fd == -1)
			{
				print_error(NULL, current->name);
				return (1);
			}
		}
		else
		{
			fd = open(current->name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (fd == -1)
			{
				print_error(NULL, current->name);
				return (1);
			}
		}
		prev = current;
		current = current->next;
	}
	if (data->table->commands[i].outfiles)
	{
		close(data->table->commands[i].fd[1]);
		data->table->commands[i].fd[1] = fd;
	}
	if (i < data->table->n_commands - 1 || data->table->commands[i].outfiles)
	{
		if (close(data->table->commands[i].fd[0]) == -1)
			print_error(NULL, ft_strjoin(data->table->commands[i].args[0], " close3"));
		dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		if (close(data->table->commands[i].fd[1]) == -1)
			print_error(NULL, ft_strjoin(data->table->commands[i].args[0], " close4"));
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

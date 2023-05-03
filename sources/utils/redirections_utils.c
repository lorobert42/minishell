/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:15 by afavre            #+#    #+#             */
/*   Updated: 2023/05/03 15:32:38 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_all_pipes(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (close(data->table->commands[j].fd[0]) == -1)
			print_error(NULL, "close pipe in");
		if (close(data->table->commands[j].fd[1]) == -1)
			print_error(NULL, "close pipe out");
		j++;
	}
}

void	close_redirections(t_data *data, int i)
{
	if (data->table->commands[i].outfiles)
		close(data->table->commands[i].fd_out);
	if (data->table->commands[i].infiles)
		close(data->table->commands[i].fd_in);
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

int	redir_pipe(t_data *data, int i)
{
	if (i > 0 && !data->table->commands[i].infiles)
	{
		dup2(data->table->commands[i - 1].fd[0], STDIN_FILENO);
	}
	if (i < data->table->n_commands - 1)
	{
		if (!data->table->commands[i].outfiles)
		{
			dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
		}
	}
	return (0);
}

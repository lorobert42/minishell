/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:49 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/03 15:26:22 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_command_io(t_file *io)
{
	t_file	*tmp;

	tmp = io;
	while (tmp)
	{
		tmp = tmp->next;
		free(io->name);
		free(io);
		io = tmp;
	}
}

void	clean_command_table(t_command_table *table)
{
	int	i;
	int	j;

	if (!table)
		return ;
	i = 0;
	while (i < table->n_commands)
	{
		clean_command_io(table->commands[i].infiles);
		clean_command_io(table->commands[i].outfiles);
		j = 0;
		while (table->commands[i].args && table->commands[i].args[j] != NULL)
		{
			free(table->commands[i].args[j]);
			j++;
		}
		free(table->commands[i].args);
		i++;
	}
	free(table->commands);
	free(table);
}

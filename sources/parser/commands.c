/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:39:37 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/30 11:26:45 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

int	command_size(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && is_string(tokens->type))
	{
		tokens = tokens->next;
		i++;
	}
	return (i);
}

void	clean_command_table(t_command_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->n_commands)
	{
		if (table->commands[i].infile)
			free(table->commands[i].infile);
		if (table->commands[i].outfile)
			free(table->commands[i].outfile);
		j = 0;
		while (table->commands[i].args[j] != NULL)
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

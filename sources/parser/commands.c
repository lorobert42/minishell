/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:39:37 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/17 10:43:37 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_token *tokens)
{
	int				i;
	t_token_type	last;

	last = tokens->type;
	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE && last == PIPE)
			return (-1);
		if (tokens->type == PIPE && last != PIPE)
			i++;
		if (tokens->type != SPACE)
			last = tokens->type;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:52 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/20 10:42:33 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_command_table	*parser(t_token *tokens)
{
	t_command_table	*table;
	int				i;

	table = malloc(sizeof(t_command_table));
	if (!table)
		return (NULL);
	table->n_commands = count_commands(tokens);
	table->commands = malloc(sizeof(t_command) * (table->n_commands + 1));
	if (!table->commands)
	{
		free(table);
		return (NULL);
	}
	i = 0;
	while (i < table->n_commands)
	{
		while (tokens && tokens->type != PIPE)
		{
			// parse simple command
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
		i++;
	}
	return (table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:39:37 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 10:53:14 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command_table	*init_table(t_token *tokens)
{
	t_command_table	*table;

	table = malloc(sizeof(t_command_table));
	if (!table)
		fatal_error(NULL, "malloc", 1);
	table->n_commands = count_commands(tokens);
	if (table->n_commands == -1)
	{
		free(table);
		g_glob.parsing = 1;
		return (NULL);
	}
	table->commands = malloc(sizeof(t_command) * table->n_commands);
	if (!table->commands)
	{
		free(table);
		fatal_error(NULL, "malloc", 1);
	}
	init_commands(table);
	return (table);
}

void	init_commands(t_command_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].infiles = NULL;
		table->commands[i].outfiles = NULL;
		table->commands[i].args = NULL;
		i++;
	}
}

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
		if (tokens->type != SPACE && tokens->type != IGNORE)
			last = tokens->type;
		tokens = tokens->next;
	}
	return (i);
}

int	command_size(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (is_string(tokens->type))
			i++;
		tokens = tokens->next;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:52 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 10:54:29 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*parse_command(t_token *tokens, t_command *command)
{
	int	i;

	tokens = extract_redirections(tokens, command);
	tokens = extract_strings(tokens, command);
	if (command->args == NULL)
	{
		command->args = malloc(sizeof(char *));
		if (!command->args)
			fatal_error(NULL, "malloc", 1);
		command->args[0] = NULL;
	}
	i = 0;
	while (command->args[0] && command->args[0][i])
	{
		command->args[0][i] = ft_tolower(command->args[0][i]);
		i++;
	}
	return (tokens);
}

void	parse_commands(t_token *tokens, t_command_table *table)
{
	int	i;

	i = 0;
	while (table && i < table->n_commands)
	{
		while (tokens && tokens->type != PIPE)
		{
			tokens = parse_command(tokens, &(table->commands[i]));
			if (g_glob.parsing == 1)
				break ;
		}
		if (tokens && tokens->type == PIPE)
		{
			if (!tokens->next)
				g_glob.parsing = 1;
			tokens = tokens->next;
		}
		i++;
	}
}

t_command_table	*parser(t_token *tokens)
{
	t_command_table	*table;

	g_glob.parsing = 0;
	table = init_table(tokens);
	parse_commands(tokens, table);
	if (g_glob.parsing == 1)
	{
		clean_command_table(table);
		return (NULL);
	}
	return (table);
}

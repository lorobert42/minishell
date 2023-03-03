/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:59:33 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/03 15:53:14 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_simple_commands(t_token *tokens)
{
	int	num_commands;
	int	i;
	int	is_command;

	num_commands = 0;
	is_command = 0;
	i = 0;
	while (tokens[i].type != END)
	{
		if (is_command == 0 && (tokens[i].type == LITERAL || \
			tokens[i].type == QUOTE || tokens[i].type == DBL_QUOTE))
		{
			is_command = 1;
			num_commands++;
		}
		else if (is_command == 1 && tokens[i].type == PIPE)
			is_command = 0;
		i++;
	}
	return (num_commands);
}

t_command_table	*parser(t_token *tokens)
{
	t_command_table	*table;

	table = malloc(sizeof(t_command_table));
	if (!table)
		return (NULL);
	table->n_commands = count_simple_commands(tokens);
	table->commands = malloc(sizeof(t_simple_command) * \
		(table->n_commands + 1));
	if (!table->commands)
		return (NULL);
	return (table);
}

int	main(int argc, char **argv)
{
	t_token			*tokens;
	t_command_table	*table;
	int				i;

	if (argc <= 1)
		return (0);
	tokens = lexer(argv[1]);
	i = 0;
	while (tokens[i].type != END)
	{
		printf("Token type: %d, value: %c\n", tokens[i].type, tokens[i].value);
		i++;
	}
	table = parser(tokens);
	printf("Number of commands: %d\n", table->n_commands);
}

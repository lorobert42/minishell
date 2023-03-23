/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:52 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/23 09:18:53 by lorobert         ###   ########.fr       */
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

int	is_redir(t_token_type t)
{
	return (t == REDIR_LEFT || t == REDIR_RIGHT \
		|| t == REDIR_APPEND || t == HERE_DOC);
}

int	is_string(t_token_type t)
{
	return (t == LITERAL || t == QUOTE_STR || t == DBL_QUOTE_STR);
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

t_token	*parse_command(t_token *tokens, t_command *command)
{
	int	i;
	int	size;

	while (tokens && tokens->type != PIPE)
	{
		if (is_redir(tokens->type))
		{
			if (!is_string(tokens->next->type))
				return (NULL);
			if (tokens->type <= REDIR_RIGHT)
			{
				command->infile = tokens->next->value;
				command->append = 0;
			}
			else
			{
				command->infile = tokens->next->value;
				command->append = 1;
			}
			tokens = tokens->next->next;
		}
		else if (is_string(tokens->type))
		{
			size = command_size(tokens);
			command->command = malloc(sizeof(char *) * (size + 1));
			if (!command->command)
				return (NULL);
			i = 0;
			while (i < size)
			{
				command->command[i] = tokens->value;
				tokens = tokens->next;
				i++;
			}
			command->command[i] = NULL;
		}
	}
	return (tokens);
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
			tokens = parse_command(tokens, &(table->commands[i]));
		}
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
		i++;
	}
	return (table);
}

int	main(int argc, char **argv)
{
	t_token			*tokens;
	t_command_table	*table;
	int				i;
	int				j;

	if (argc <= 1)
		return (0);
	tokens = lexer(argv[1]);
	table = parser(tokens);
	i = 0;
	while (i < table->n_commands)
	{
		printf("IN: %s\nOUT: %s\n", table->commands[i].infile, table->commands[i].outfile);
		j = 0;
		while (table->commands[i].command[j] != NULL)
		{
			printf("%s", table->commands[i].command[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

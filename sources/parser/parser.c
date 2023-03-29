/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:52 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/29 09:46:49 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*extract_redirection(t_token *tokens, t_command *command)
{
	if (!is_string(tokens->next->type))
		return (NULL);
	if (tokens->type == REDIR_LEFT)
		command->infile = tokens->next->value;
	else if (tokens->type == REDIR_RIGHT)
		command->outfile = tokens->next->value;
	else if (tokens->type == HERE_DOC)
		command->infile = tokens->next->value;
	else
		command->outfile = tokens->next->value;
	command->append = tokens->type >= HERE_DOC;
	tokens = tokens->next->next;
	return (tokens);
}

t_token	*extract_string(t_token *tokens, t_command *command)
{
	int	i;
	int	size;

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
	return (tokens);
}

t_token	*parse_command(t_token *tokens, t_command *command)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_redir(tokens->type))
		{
			tokens = extract_redirection(tokens, command);
		}
		else if (is_string(tokens->type))
		{
			tokens = extract_string(tokens, command);
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

/* int	main(int argc, char **argv)
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
			printf("%s ", table->commands[i].command[j]);
			j++;
		}
		printf("\n");
		i++;
	}
} */

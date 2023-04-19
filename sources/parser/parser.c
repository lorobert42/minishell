/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:52 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/19 10:05:35 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	extract_redirection(t_token *tokens, t_command *command)
{
	t_token	*start;
	t_token	*next;

	start = tokens;
	while (tokens && tokens->type != PIPE)
	{
		if (is_redir(tokens->type))
		{
			if (!tokens->next || !is_string(tokens->next->type))
				// ERROR
				return ;
			if (tokens->type == REDIR_LEFT || tokens->type == HERE_DOC)
				command->infile = ft_strdup(tokens->next->value);
			else
				command->outfile = ft_strdup(tokens->next->value);
			next = tokens->next->next;
			delete_token(start, tokens->next);
			delete_token(start, tokens);
			tokens = next;
		}
		else
			tokens = tokens->next;
	}
}

t_token	*extract_string(t_token *tokens, t_command *command)
{
	int	i;
	int	size;

	size = command_size(tokens);
	command->args = malloc(sizeof(char *) * (size + 1));
	if (!command->args)
		return (NULL);
	i = 0;
	while (i < size)
	{
		command->args[i] = ft_strdup(tokens->value);
		tokens = tokens->next;
		i++;
	}
	command->args[i] = NULL;
	return (tokens);
}

t_token	*parse_command(t_token *tokens, t_command *command)
{
	int	i;

	extract_redirection(tokens, command);
	while (tokens && tokens->type != PIPE)
	{
		if (is_string(tokens->type))
		{
			tokens = extract_string(tokens, command);
		}
		if (g_glob.parsing == 1)
			return (NULL);
	}
	if (command->args == NULL)
	{
		command->args = malloc(sizeof(char *));
		if (!command->args)
			return (NULL);
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

void	init_commands(t_command_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].args = NULL;
		i++;
	}
}

t_command_table	*init_table(t_token *tokens)
{
	t_command_table	*table;

	table = malloc(sizeof(t_command_table));
	if (!table)
		return (NULL);
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
		return (NULL);
	}
	init_commands(table);
	return (table);
}

t_command_table	*parser(t_token *tokens)
{
	t_command_table	*table;
	int				i;

	g_glob.parsing = 0;
	table = init_table(tokens);
	if (!table)
		return (NULL);
	i = 0;
	while (i < table->n_commands)
	{
		table->commands[i].infile = NULL;
		table->commands[i].outfile = NULL;
		table->commands[i].append = 0;
		while (tokens && tokens->type != PIPE)
		{
			tokens = parse_command(tokens, &(table->commands[i]));
			if (g_glob.parsing == 1)
			{
				clean_command_table(table);
				return (NULL);
			}
		}
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
		i++;
	}
	return (table);
}

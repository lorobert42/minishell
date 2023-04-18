/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:25:52 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/17 17:23:58 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*extract_redirection(t_token *tokens, t_command *command)
{
	if (tokens->next == NULL || !is_string(tokens->next->type))
	{
		g_glob[0] = 1;
		return (NULL);
	}
	if (tokens->type == REDIR_LEFT)
		command->infile = ft_strdup(tokens->next->value);
	else if (tokens->type == REDIR_RIGHT)
		command->outfile = ft_strdup(tokens->next->value);
	else if (tokens->type == HERE_DOC)
		command->infile = ft_strdup(tokens->next->value);
	else
		command->outfile = ft_strdup(tokens->next->value);
	command->append = tokens->type >= HERE_DOC;
	tokens = tokens->next->next;
	return (tokens);
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
		if (g_glob[0] == 1)
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
		g_glob[0] = 1;
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
			if (g_glob[0] == 1)
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

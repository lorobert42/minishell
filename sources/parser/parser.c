/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:59:33 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/02 13:07:25 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_io_in(char *token)
{
	return (!ft_strncmp(token, "<", 2));
}

int	is_io_out(char *token)
{
	return (!ft_strncmp(token, ">", 2));
}

int	is_io(char *token)
{
	return (is_io_in(token) || is_io_out(token));
}

int	is_pipe(char *token)
{
	return (!ft_strncmp(token, "|", 2));
}

int	count_simple_commands(t_list *tokens)
{
	int	commands;
	int	is_command;

	commands = 0;
	is_command = 0;
	while (tokens)
	{
		if (!is_command && !is_io(tokens->content))
		{
			is_command = 1;
			commands++;
		}
		else if (is_io(tokens->content))
		{
			is_command = 0;
			tokens = tokens->next;
			if (is_io(tokens->content))
				tokens = tokens->next;
		}
		else if (is_pipe(tokens->content))
			is_command = 0;
		tokens = tokens->next;
	}
	return (commands);
}

int	command_size(t_list *tokens)
{
	int	size;

	size = 0;
	while (tokens)
	{
		if (is_io(tokens->content))
			return (size);
		else if (is_pipe(tokens->content))
			return (size);
		size++;
		tokens = tokens->next;
	}
	return (size);
}

t_simple_command	*init_simple_command(int num)
{
	t_simple_command	*command;

	command = malloc(sizeof(t_simple_command));
	if (!command)
		return (NULL);
	command->command = malloc(sizeof(char *) * (num + 1));
	if (!command->command)
		return (NULL);
	command->command[num] = NULL;
	return (command);
}

t_command_table	*parser(t_list *tokens)
{
	t_command_table	*table;
	int				i;
	int				j;
	int				c_size;

	table = malloc(sizeof(t_command_table));
	table->commands_num = count_simple_commands(tokens);
	table->commands = malloc(sizeof(t_simple_command) * (table->commands_num + 1));
	i = 0;
	while (tokens)
	{
		if (is_io_in(tokens->content))
		{
			if (is_io_in(tokens->next->content))
				tokens = tokens->next;
			tokens = tokens->next;
			table->in = tokens->content;
		}
		else if (is_io_out(tokens->content))
		{
			if (is_io_out(tokens->next->content))
				tokens = tokens->next;
			tokens = tokens->next;
			table->out = tokens->content;
		}
		else if (!is_pipe(tokens->content))
		{
			c_size = command_size(tokens);
			j = 0;
			table->commands[i] = init_simple_command(c_size);
			while (j < c_size)
			{
				table->commands[i]->command[j] = tokens->content;
				if (j + 1 < c_size)
					tokens = tokens->next;
				j++;
			}
			i++;
		}
		tokens = tokens->next;
	}
	table->commands[table->commands_num] = NULL;
	return (table);
}

int	main(int argc, char **argv)
{
	t_list			*tokens;
	t_command_table	*table;

	(void)argc;
	tokens = lexer(argv[1]);
	table = parser(tokens);
	printf("Number of simple commands: %d\n", table->commands_num);
	printf("IN: %s\n", table->in);
	for (int i = 0; i < table->commands_num; i++)
	{
		printf("Command %d\n", i);
		int j = 0;
		while (table->commands[i]->command[j])
		{
			printf("%s", table->commands[i]->command[j]);
			j++;
		}
		printf("\n");
	}
}

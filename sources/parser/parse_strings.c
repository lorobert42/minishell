/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:24:04 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 10:54:10 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*extract_string(t_token *tokens, t_command *command)
{
	int	i;
	int	size;

	size = command_size(tokens);
	command->args = malloc(sizeof(char *) * (size + 1));
	if (!command->args)
		fatal_error(NULL, "malloc", 1);
	i = 0;
	while (i < size && tokens)
	{
		if (!tokens->value || tokens->type == IGNORE)
		{
			tokens = tokens->next;
			continue ;
		}
		command->args[i] = ft_strdup(tokens->value);
		tokens = tokens->next;
		i++;
	}
	command->args[i] = NULL;
	return (tokens);
}

t_token	*extract_strings(t_token *tokens, t_command *command)
{
	while (tokens && tokens->type != PIPE)
	{
		if (is_string(tokens->type))
		{
			tokens = extract_string(tokens, command);
		}
		else
			tokens = tokens->next;
		if (g_glob.parsing == 1)
			return (NULL);
	}
	return (tokens);
}

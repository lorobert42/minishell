/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:26:21 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 13:28:56 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		fatal_error(NULL, "malloc", 1);
	token->next = NULL;
	token->type = type;
	token->value = value;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*current;

	current = *tokens;
	if (!current)
	{
		*tokens = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_token	*delete_token(t_token *start, t_token *to_del)
{
	t_token	*current;

	if (start == to_del)
	{
		start = to_del->next;
		return (start);
	}
	current = start;
	while (current->next != to_del)
		current = current->next;
	current->next = to_del->next;
	free(to_del->value);
	free(to_del);
	return (start);
}

void	clean_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		free(tokens->value);
		next = tokens->next;
		free(tokens);
		tokens = next;
	}
}

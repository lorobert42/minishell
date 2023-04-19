/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:26:21 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/19 09:15:42 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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

void	delete_token(t_token *start, t_token *to_del)
{
	while (start->next != to_del)
		start = start->next;
	start->next = to_del->next;
	free(to_del->value);
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

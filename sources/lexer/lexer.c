/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:34:19 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/11 12:51:24 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	extract_quote_string(t_token **tokens, char *command)
{
	int				i;
	t_token_type	t;
	int				in_quote;

	in_quote = command[0];
	i = 1;
	while (command[i])
	{
		if (!in_quote && issep(command[i]))
			break ;
		if (is_quote(command[i]) && command[i] == in_quote)
		in_quote = 0;
		else if (is_quote(command[i]) && !in_quote)
			in_quote = command[i];
		i++;
	}
	if (command[0] == '"')
		t = DBL_QUOTE_STR;
	else
		t = QUOTE_STR;
	add_token(tokens, create_token(ft_substr(command, 0, i), t));
	return (i + 1);
}

int	extract_redir(t_token **tokens, char *command)
{
	if (command[0] == '<' && command[1] == '<')
	{
		add_token(tokens, create_token(ft_substr(command, 0, 2), HERE_DOC));
		return (2);
	}
	else if (command[0] == '<')
	{
		add_token(tokens, create_token(ft_substr(command, 0, 1), REDIR_LEFT));
		return (1);
	}
	else if (command[0] == '>' && command[1] == '>')
	{
		add_token(tokens, create_token(ft_substr(command, 0, 2), REDIR_APPEND));
		return (2);
	}
	else
	{
		add_token(tokens, create_token(ft_substr(command, 0, 1), REDIR_RIGHT));
		return (1);
	}
}

int	extract_literal(t_token **tokens, char *command)
{
	int				i;
	t_token_type	t;

	t = LITERAL;
	i = 0;
	while (command[i] && (!issep(command[i]) || t != LITERAL))
	{
		if (t == LITERAL && command[i] == '\'')
			t = QUOTE_STR;
		else if (t == LITERAL && command[i] == '"')
			t = DBL_QUOTE_STR;
		else if (t != LITERAL && quote_type(command[i]) == t)
			t = LITERAL;
		i++;
	}
	add_token(tokens, create_token(ft_substr(command, 0, i), t));
	return (i);
}

int	extract_token(t_token **tokens, char *command)
{
	int	i;

	i = 0;
	while (ft_isspace(command[i]))
		i++;
	if (command[i] == '\0')
		return (i);
	else if (command[i] == '"' || command[i] == '\'')
		i += extract_quote_string(tokens, &command[i]);
	else if (command[i] == '|')
	{
		add_token(tokens, create_token(ft_substr(&command[i], 0, 1), PIPE));
		i++;
	}
	else if (command[i] == '<' || command[i] == '>')
		i += extract_redir(tokens, &command[i]);
	else
		i += extract_literal(tokens, &command[i]);
	return (i);
}

t_token	*lexer(char *command)
{
	t_token	*tokens;
	size_t	i;

	if (!command)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (i < ft_strlen(command))
	{
		i += extract_token(&tokens, &command[i]);
	}
	return (tokens);
}

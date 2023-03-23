/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:34:19 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/23 08:55:01 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_quote_string(t_token **tokens, char *command)
{
	int				i;
	t_token_type	t;

	i = 1;
	while (command[i] && command[i] != command[0])
		i++;
	while (command[i] && !issep(command[i]))
		i++;
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
	while (command[i] && !issep(command[i]))
	{
		if (t == LITERAL && command[i] == '\'')
			t = QUOTE_STR;
		else if (t == LITERAL && command[i] == '"')
			t = DBL_QUOTE_STR;
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

	tokens = NULL;
	i = 0;
	while (i < ft_strlen(command))
	{
		i += extract_token(&tokens, &command[i]);
	}
	return (tokens);
}

/* int	main(int argc, char **argv)
{
	t_token	*tokens;

	if (argc <= 1)
		return (0);
	tokens = lexer(argv[1]);
	while (tokens)
	{
		printf("Token type: %d, value: %s\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
} */

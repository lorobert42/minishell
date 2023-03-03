/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:34:19 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/03 15:05:56 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

t_token_type	get_token_type(char c)
{
	if (c == '<')
		return (REDIR_LEFT);
	else if (c == '>')
		return (REDIR_RIGHT);
	else if (c == '|')
		return (PIPE);
	else if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DBL_QUOTE);
	else if (ft_isspace(c))
		return (SPACE);
	else
		return (LITERAL);
}

t_token	*lexer(char *command)
{
	t_token	*tokens;
	int		i;

	tokens = malloc(sizeof(t_token) * (ft_strlen(command) + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (command[i])
	{
		tokens[i].type = get_token_type(command[i]);
		tokens[i].value = command[i];
		i++;
	}
	tokens[i].type = END;
	return (tokens);
}

/* int	main(int argc, char **argv)
{
	t_token	*tokens;
	int		i;

	if (argc <= 1)
		return (0);
	tokens = lexer(argv[1]);
	i = 0;
	while (tokens[i].type != END)
	{
		printf("Token type: %d, value: %c\n", tokens[i].type, tokens[i].value);
		i++;
	}
} */

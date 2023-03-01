/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:34:19 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/01 13:29:31 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ');
}

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

t_list	*lexer(char *command)
{
	t_list	*tokens;
	t_list	*next;
	int		i;
	int		start;
	char	*token;
	int		is_quote;
	int		is_dquote;

	i = 0;
	start = 0;
	is_quote = 0;
	is_dquote = 0;
	tokens = NULL;
	token = NULL;
	while (command[i])
	{
		if (command[i] == '\'' && !is_dquote)
		{
			if (is_quote)
				is_quote = 0;
			else
			{
				if (start == i)
				{
					token = ft_substr(command, start, i - start + 1);
					start = i + 1;
				}
				else
				{
					token = ft_substr(command, start, i - start);
					start = i;
				}
				is_quote = 1;
			}
		}
		else if (command[i] == '"' && !is_quote)
		{
			if (is_dquote)
				is_dquote = 0;
			else
			{
				if (start == i)
				{
					token = ft_substr(command, start, i - start + 1);
					start = i + 1;
				}
				else
				{
					token = ft_substr(command, start, i - start);
					start = i;
				}
				is_dquote = 1;
			}
		}
		else if (ft_isspace(command[i]) && !is_quote && !is_dquote)
		{
			token = ft_substr(command, start, i - start);
			start = i + 1;
		}
		else if (is_special(command[i]) && !is_quote && !is_dquote)
		{
			if (start == i)
			{
				token = ft_substr(command, start, i - start + 1);
				start = i + 1;
			}
			else
			{
				token = ft_substr(command, start, i - start);
				start = i;
			}
		}
		if (!tokens && token)
		{
			tokens = ft_lstnew(token);
			next = tokens;
		}
		else if (tokens && token)
		{
			next->next = ft_lstnew(token);
			next = next->next;
		}
		token = NULL;
		i++;
	}
	token = ft_substr(command, start, i - start);
	next->next = ft_lstnew(token);
	return (tokens);
}

int	main(int argc, char **argv)
{
	t_list	*tokens;

	(void)argc;
	tokens = lexer(argv[1]);
	while (tokens)
	{
		printf("%s\n", (char *)tokens->content);
		tokens = tokens->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:05:06 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/30 10:09:45 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	count_quotes(char *s)
{
	int	n;
	int	i;
	int	in_quote;

	i = 0;
	n = 0;
	in_quote = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			if (!in_quote)
			{
				in_quote = s[i];
				n++;
			}
			else if (in_quote && s[i] == in_quote)
			{
				in_quote = 0;
				n++;
			}
		}
		i++;
	}
	return (n);
}

int	check_unclosed_quotes(t_token *token)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (token->value[i])
	{
		if (!in_quotes && is_quote(token->value[i]))
			in_quotes = token->value[i];
		else if (in_quotes && is_quote(token->value[i]) && \
			in_quotes == token->value[i])
			in_quotes = 0;
		i++;
	}
	if (in_quotes)
		return (1);
	return (0);
}

int	delete_quotes(t_token *token)
{
	int		i;
	int		j;
	int		in_quote;
	char	*new;

	if (check_unclosed_quotes(token) == 1)
		return (1);
	j = count_quotes(token->value);
	if (j == 0)
		return (0);
	new = malloc(sizeof(char) * (ft_strlen(token->value) - j + 1));
	if (!new)
		return (1);
	i = 0;
	j = 0;
	in_quote = 0;
	while (token->value[i])
	{
		if (!is_quote(token->value[i]) || (is_quote(token->value[i]) && in_quote && in_quote != token->value[i]))
		{
			if (in_quote == token->value[i])
				in_quote = 0;
			new[j] = token->value[i];
			j++;
		}
		else if (in_quote == 0)
			in_quote = token->value[i];
		i++;
	}
	new[j] = '\0';
	free(token->value);
	token->value = new;
	return (0);
}

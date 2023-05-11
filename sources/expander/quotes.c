/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:05:06 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/11 12:50:16 by lorobert         ###   ########.fr       */
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

int	check_unclosed_quotes(char *str)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (!in_quotes && is_quote(str[i]))
			in_quotes = str[i];
		else if (in_quotes && is_quote(str[i]) && \
			in_quotes == str[i])
			in_quotes = 0;
		i++;
	}
	if (in_quotes)
		return (1);
	return (0);
}

char	*unquote_str(char *str, char *new)
{
	int	i;
	int	j;
	int	in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		if (!is_quote(str[i]) || (is_quote(str[i]) && in_quote \
			&& in_quote != str[i]))
		{
			new[j] = str[i];
			j++;
		}
		else if (in_quote == 0)
			in_quote = str[i];
		else if (is_quote(str[i]) && in_quote)
			in_quote = 0;
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*delete_quotes(char *str)
{
	int		i;
	char	*new;

	if (check_unclosed_quotes(str) == 1)
	{
		free(str);
		return (NULL);
	}
	i = count_quotes(str);
	if (i == 0)
		return (str);
	new = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new)
		fatal_error(NULL, "malloc", 1);
	return (unquote_str(str, new));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/29 15:11:19 by lorobert         ###   ########.fr       */
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

void	delete_quotes(t_token *token)
{
	int		i;
	int		j;
	int		in_quote;
	char	*new;

	j = count_quotes(token->value);
	if (j == 0)
		return ;
	new = malloc(sizeof(char) * (ft_strlen(token->value) - j + 1));
	if (!new)
		return ;
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
}

void	expand_token(t_token *token, int pos, t_env *env)
{
	char	*var;
	char	*new;
	char	*varname;
	int		end;
	int		i;
	int		j;

	end = pos;
	// TODO: find end of variable name ($1TEST for example)
	while (token->value[end] && !issep(token->value[end]) && !is_quote(token->value[end]))
		end++;
	varname = ft_substr(token->value, pos, end - pos);
	var = ft_getenv(env, varname);
	free(varname);
	if (!var)
		var = ft_strdup("");
	new = malloc(sizeof(char) * (ft_strlen(token->value) - (end - pos) + ft_strlen(var)));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while (token->value[i])
	{
		if (i >= pos && i <= end)
		{
			i = 0;
			while (var[i])
			{
				new[j] = var[i];
				j++;
				i++;
			}
			i = end;
		}
		else if (i != pos - 1)
		{
			new[j] = token->value[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(var);
	free(token->value);
	token->value = new;
}

void	check_expansion(t_token *token, t_env *env)
{
	int	simple;
	int	i;

	simple = 0;
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' && !simple)
			simple = 1;
		else if (token->value[i] == '\'' && simple)
			simple = 0;
		else if (token->value[i] == '$' && !simple)
			expand_token(token, i + 1, env);
		i++;
	}
}

int	expander(t_token *tokens, t_env *env)
{
	while (tokens)
	{
		if (is_string(tokens->type))
		{
			check_expansion(tokens, env);
			delete_quotes(tokens);
		}
		tokens = tokens->next;
	}
	return (0);
}

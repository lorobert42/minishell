/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/30 10:05:35 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			if (delete_quotes(tokens) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

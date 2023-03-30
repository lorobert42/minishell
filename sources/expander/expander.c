/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/30 11:18:07 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_variable_end(char *s)
{
	int	i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (i != 0)
		return (i);
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

int	get_variable(char *s, char **var, t_env *env)
{
	char	*varname;
	int		end;

	end = get_variable_end(s);
	varname = ft_substr(s, 0, end);
	*var = ft_getenv(env, varname);
	free(varname);
	if (!*var)
		*var = ft_strdup("");
	return (end);
}

int	expand_token(t_token *token, int pos, t_env *env)
{
	char	*var;
	char	*new;
	int		end;
	int		i;
	int		j;

	end = get_variable(&token->value[pos], &var, env);
	if (!var)
		return (1);
	new = malloc(sizeof(char) * (ft_strlen(token->value) - (end - pos) + ft_strlen(var)));
	if (!new)
	{
		free(var);
		return (1);
	}
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
	return (0);
}

int	check_expansion(t_token *token, t_env *env)
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
			if (expand_token(token, i + 1, env))
				return (1);
		i++;
	}
	return (0);
}

int	expander(t_token *tokens, t_env *env)
{
	while (tokens)
	{
		if (is_string(tokens->type))
		{
			if (check_expansion(tokens, env))
				return (1);
			if (delete_quotes(tokens) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

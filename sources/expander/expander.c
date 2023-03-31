/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/31 13:42:19 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_variable_end(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '?')
		return (i + 1);
	else if (ft_isdigit(s[i]))
		return (0);
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

int	get_variable(char *s, char **var, char **env)
{
	char	*varname;
	int		end;

	end = get_variable_end(s);
	if (end == 0)
		return (0);
	varname = ft_substr(s, 0, end);
	if (ft_strncmp(varname, "?", 2) == 0)
		*var = ft_itoa(g_glob);
	else
		*var = getenv_value(env, varname);
	free(varname);
	if (!*var)
		*var = ft_strdup("");
	return (end);
}

int	expand_token(t_token *token, int pos, char **env)
{
	char	*var;
	char	*new;
	int		end;
	int		size;

	end = get_variable(&token->value[pos], &var, env) + pos;
	if (end == 1)
		return (1);
	if (!var)
		return (-1);
	size = ft_strlen(token->value) - (end - pos) + ft_strlen(var);
	new = ft_calloc(sizeof(char), size);
	if (!new)
	{
		free(var);
		return (-1);
	}
	ft_strlcat(new, token->value, pos);
	ft_strlcat(new, var, ft_strlen(new) + ft_strlen(var) + 1);
	ft_strlcat(new, &token->value[end], size);
	end = ft_strlen(var);
	free(var);
	free(token->value);
	token->value = new;
	return (end);
}

int	check_expansion(t_token *token, char **env)
{
	int	simple;
	int	i;
	int	res;

	simple = 0;
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'' && !simple)
			simple = 1;
		else if (token->value[i] == '\'' && simple)
			simple = 0;
		else if (token->value[i] == '$' && !simple)
		{
			res = expand_token(token, i + 1, env);
			if (res == -1)
				return (1);
			i += res;
		}
		i++;
	}
	return (0);
}

int	expander(t_token *tokens, char **env)
{
	while (tokens)
	{
		if (is_string(tokens->type))
		{
			if (check_expansion(tokens, env) == 1)
				return (1);
			if (delete_quotes(tokens) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

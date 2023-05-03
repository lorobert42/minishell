/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/03 12:18:52 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_variable_end(char *s, int in_quotes)
{
	int	i;

	i = 0;
	if (s[i] == '?')
		return (i + 1);
	else if (in_quotes && s[i] == in_quotes)
		return (0);
	else if (!in_quotes && is_quote(s[i]))
		return (-1);
	else if (ft_isdigit(s[i]))
		return (0);
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	return (i);
}

int	get_variable(char *s, char **var, int in_quotes, char **env)
{
	char	*varname;
	int		end;

	end = get_variable_end(s, in_quotes);
	if (end == 0)
		return (0);
	if (end == -1)
	{
		end = 0;
		varname = ft_strdup("");
	}
	else
		varname = ft_substr(s, 0, end);
	if (ft_strncmp(varname, "?", 2) == 0)
		*var = ft_itoa(g_glob.error);
	else
		*var = getenv_value(env, varname);
	free(varname);
	if (!*var)
		*var = ft_strdup("");
	return (end);
}

int	expand_token(char **str, int pos, int in_quotes, char **env)
{
	char	*var;
	char	*new;
	int		end;
	int		size;

	var = NULL;
	end = get_variable(&(*str)[pos], &var, in_quotes, env);
	if (end == 0 && !var)
		return (1);
	if (!var)
		return (-1);
	end += pos;
	size = ft_strlen(*str) - (end - pos) + ft_strlen(var);
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
	{
		free(var);
		return (-1);
	}
	ft_strlcat(new, *str, pos);
	ft_strlcat(new, var, ft_strlen(new) + ft_strlen(var) + 1);
	ft_strlcat(new, &(*str)[end], size);
	end = ft_strlen(var);
	free(var);
	free(*str);
	*str = new;
	return (end);
}

int	check_expansion(char **str, char **env)
{
	int	in_quotes;
	int	i;
	int	res;

	in_quotes = 0;
	i = 0;
	while ((*str)[i])
	{
		if (is_quote((*str)[i]) && !in_quotes)
			in_quotes = (*str)[i];
		else if (is_quote((*str)[i]) && in_quotes == (*str)[i])
			in_quotes = 0;
		else if ((*str)[i] == '$' && in_quotes != '\'')
		{
			res = expand_token(str, i + 1, in_quotes, env);
			if (res == -1)
				return (1);
			i += res - 1;
		}
		i++;
	}
	return (0);
}

int	expander(t_token *tokens, char **env)
{
	int	heredoc;

	heredoc = 0;
	while (tokens)
	{
		if (tokens->type == HERE_DOC)
			heredoc = 1;
		if (is_string(tokens->type) && !heredoc)
		{
			if (check_expansion(&tokens->value, env) == 1)
				return (1);
			if (tokens->value[0] == '\0')
			{
				free(tokens->value);
				tokens->value = NULL;
				tokens = tokens->next;
				continue ;
			}
			tokens->value = delete_quotes(tokens->value);
			if (tokens->value == NULL)
				return (1);
		}
		else if (heredoc && tokens->type != HERE_DOC)
			heredoc = 0;
		tokens = tokens->next;
	}
	return (0);
}

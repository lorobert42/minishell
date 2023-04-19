/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/19 10:04:11 by lorobert         ###   ########.fr       */
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
	while (ft_isalnum(s[i]) || s[i] == '_')
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
		*var = ft_itoa(g_glob.error);
	else
		*var = getenv_value(env, varname);
	free(varname);
	if (!*var)
		*var = ft_strdup("");
	return (end);
}

int	expand_token(char **str, int pos, char **env)
{
	char	*var;
	char	*new;
	int		end;
	int		size;

	end = get_variable(&(*str)[pos], &var, env);
	if (end == 0)
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
	int	simple;
	int	i;
	int	res;

	simple = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' && !simple)
			simple = 1;
		else if ((*str)[i] == '\'' && simple)
			simple = 0;
		else if ((*str)[i] == '$' && !simple)
		{
			res = expand_token(str, i + 1, env);
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

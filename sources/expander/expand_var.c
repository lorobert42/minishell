/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:43:54 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/04 13:45:04 by lorobert         ###   ########.fr       */
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
	end += pos;
	size = ft_strlen(*str) - (end - pos) + ft_strlen(var);
	new = ft_calloc(sizeof(char), size + 1);
	if (!new)
		fatal_error(NULL, "malloc", 1);
	ft_strlcat(new, *str, pos);
	ft_strlcat(new, var, ft_strlen(new) + ft_strlen(var) + 1);
	ft_strlcat(new, &(*str)[end], size);
	end = ft_strlen(var);
	free(var);
	free(*str);
	*str = new;
	return (end);
}

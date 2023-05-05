/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:48:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 13:50:09 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_expansion(char **str, char **env)
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
			i += res - 1;
		}
		i++;
	}
}

char	*expand_home(char *str, char **env)
{
	char	*new;
	char	*home;

	home = getenv_value(env, "HOME");
	if (!home)
		home = ft_strdup("");
	new = ft_strjoin(home, str + 1);
	free(str);
	return (new);
}

t_token	*expand(t_token *tokens, char **env)
{
	if (!ft_strncmp(tokens->value, "~", 2) || \
		!ft_strncmp(tokens->value, "~/", 2))
		tokens->value = expand_home(tokens->value, env);
	else
		check_expansion(&tokens->value, env);
	if (tokens->value[0] == '\0')
	{
		tokens->type = IGNORE;
		return (tokens);
	}
	tokens->value = delete_quotes(tokens->value);
	if (tokens->value == NULL)
		return (NULL);
	return (tokens);
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
			tokens = expand(tokens, env);
			if (!tokens)
				return (1);
		}
		else if (heredoc && tokens->type != HERE_DOC)
			heredoc = 0;
		tokens = tokens->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:13:38 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 10:54:19 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_redirection(t_file **files, char *name, int append)
{
	t_file	*new;
	t_file	*to_replace;

	new = malloc(sizeof(t_file));
	if (!new)
		fatal_error(NULL, "malloc", 1);
	new->name = ft_strdup(name);
	new->append = append;
	new->next = NULL;
	if (!*files)
	{
		*files = new;
		return ;
	}
	to_replace = *files;
	while (to_replace->next != NULL)
		to_replace = to_replace->next;
	to_replace->next = new;
}

int	extract_redirection(t_token *tokens, t_command *command)
{
	if (!tokens->next || !is_string(tokens->next->type))
	{
		g_glob.parsing = 1;
		return (1);
	}
	if (tokens->type == REDIR_LEFT || tokens->type == HERE_DOC)
		add_redirection(&command->infiles, tokens->next->value, \
			tokens->type == HERE_DOC);
	else
		add_redirection(&command->outfiles, tokens->next->value, \
			tokens->type == REDIR_APPEND);
	return (0);
}

t_token	*extract_redirections(t_token *tokens, t_command *command)
{
	t_token	*start;

	start = tokens;
	while (tokens && tokens->type != PIPE)
	{
		if (is_redir(tokens->type))
		{
			if (extract_redirection(tokens, command) == 1)
				return (NULL);
			tokens->type = IGNORE;
			tokens->next->type = IGNORE;
			tokens = tokens->next->next;
		}
		else
			tokens = tokens->next;
	}
	return (start);
}

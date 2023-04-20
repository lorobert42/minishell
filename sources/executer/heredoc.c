/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:43 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/20 13:46:22 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_heredoc(t_data *data)
{
	int			i;
	t_command	*c;
	t_file		*current;

	c = data->table->commands;
	i = 0;
	while (i < data->table->n_commands)
	{
		current = c[i].infiles;
		while (current)
		{
			if (current->append)
			{
				pipe(c[i].fd);
				heredoc(&current->name, c[i].fd[1], data);
				close(c[i].fd[1]);
			}
			current = current->next;
		}
		i++;
	}
}

/*
HEREDOCS are processed before executing any command: 
	(echo test 1>&2 | sed 's/l/e/g' <<EOF).
Environment variables are expanded inside HEREDOCS execpt if delimiter contains
	quotes.
*/
void	heredoc_loop(t_data *data, char **delim, int expand, int fd)
{
	char	*line;

	line = "";
	while (line)
	{
		line = readline("> ");
		if (!line)
			return ;
		if (ft_strncmp(line, *delim, ft_strlen(*delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			check_expansion(&line, data->env);
		if (line)
		{
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
			free(line);
		}
	}
}

int	heredoc(char **delim, int fd, t_data *data)
{
	int		expand;
	int		i;

	expand = 1;
	i = 0;
	while ((*delim)[i])
	{
		if ((*delim)[i] == '\'' || (*delim)[i] == '"')
			expand = 0;
		i++;
	}
	*delim = delete_quotes(*delim);
	if (*delim == NULL)
		return (-1);
	heredoc_loop(data, delim, expand, fd);
	return (0);
}

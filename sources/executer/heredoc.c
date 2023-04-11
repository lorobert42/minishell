/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:43 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/06 15:36:36 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_heredoc(t_data *data)
{
	int			i;
	t_command	*c;

	c = data->table->commands;
	i = 0;
	while (i < data->table->n_commands)
	{
		if (c[i].infile && c[i].append)
		{
			pipe(c[i].fd);
			heredoc(&c[i].infile, c[i].fd[1], data);
			close(c[i].fd[1]);
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
int	heredoc(char **delim, int fd, t_data *data)
{
	int		expand;
	int		i;
	char	*line;

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
	line = "";
	while (line)
	{
		line = readline("> ");
		if (!line)
			return (0);
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
	return (0);
}

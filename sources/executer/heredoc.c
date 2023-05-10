/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:43 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/10 12:58:04 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_heredoc(t_data *data, t_file *current, t_command *c, int i)
{
	char		*tmp;
	char		*i_str;

	i_str = ft_itoa(i);
	tmp = ft_strjoin("/tmp/minishell_heredoc_", i_str);
	free(i_str);
	c[i].fd[1] = open(tmp, \
					O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (c[i].fd[1] == -1)
	{
		print_error(NULL, "heredoc tmp file");
		free(tmp);
		g_glob.error = 1;
		return (1);
	}
	if (heredoc(&current->name, c[i].fd[1], data))
	{
		close(c[i].fd[1]);
		return (1);
	}
	close(c[i].fd[1]);
	free(current->name);
	current->name = tmp;
	return (0);
}

int	set_heredoc(t_data *data)
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
				if (execute_heredoc(data, current, c, i) == 1)
					return (1);
			}
			current = current->next;
		}
		i++;
	}
	return (0);
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
	int			expand;
	int			i;
	pid_t		pid;

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
	pid = fork();
	if (pid == 0)
		heredoc_child(delim, fd, expand, data);
	else
	{
		if (heredoc_parent(pid, data))
			return (1);
	}
	return (0);
}

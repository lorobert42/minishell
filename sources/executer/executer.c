/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/04/26 09:39:39 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_path(t_data *data, int num)
{
	char	*env;
	char	**path;
	int		i;

	env = ft_getenv(data->env, "PATH");
	if (env != NULL)
	{
		path = ft_split(env, ':');
		i = 0;
		while (path[i] != NULL)
		{
			if (access(get_path(path[i], data->table->commands[num].args[0]), \
		F_OK | R_OK) == 0)
				return (get_path(path[i], data->table->commands[num].args[0]));
			i++;
		}
		clear_split(path);
	}
	return (NULL);
}

void	children(t_data *data, int i)
{
	char	*path;

	if (is_builtins(data->table->commands[i].args))
		exec_builtins(data, data->table->commands[i].args);
	else
	{
		termios_restore_ctrl();
		path = find_path(data, i);
		if (path != NULL)
		{
			execve(path, data->table->commands[i].args, data->env);
		}
		else
		{
			ft_printf("🤷 Hérishell: %s: a pas trouver ... 🤷\n", data->table->commands[i].args[0]);
			termios_remove_ctrl();
		}
	}
	exit(0);
}

void	execution_loop(t_data *data)
{
	pid_t	pid;
	int		i;
	int		status;

	i = 0;
	while (i < data->table->n_commands)
	{
		g_glob.status = 1;
		pipe(data->table->commands[i].fd);
		pid = fork();
		g_glob.nb_children += 1;
		if (pid == 0)
		{
			if (data->table->commands[i].infiles)
			{
				if (redir_file_in(data, i))
					exit(1);
			}
			if (data->table->commands[i].outfiles)
			{
				if (redir_file_out(data, i))
					exit(1);
			}
			redir_pipe(data, i);
			children(data, i);
		}
		else
		{
			if (i > 0)
			{
				close_pipe(data, i - 1);
			}
		}
		i++;
	}
	if (i > 0)
	{
		close_pipe(data, i - 1);
	}
	while (g_glob.nb_children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			g_glob.nb_children--;
		}
	}
	i = -1;
	while (++i < data->table->n_commands)
		delete_heredoc(data, i);
	if (WIFEXITED(status))
		g_glob.error = WEXITSTATUS(status);
	termios_remove_ctrl();
}

int	execute(t_data *data)
{
	set_heredoc(data);
	if (data->table->n_commands == 1)
	{
		if (is_builtins(data->table->commands[0].args))
		{
			data->saved_io[0] = dup(STDIN_FILENO);
			data->saved_io[1] = dup(STDOUT_FILENO);
			if (redir_file_in(data, 0))
			{
				close_redirections(data, 0);
				return (1);
			}
			if (redir_file_out(data, 0))
			{
				close_redirections(data, 0);
				return (1);
			}
			exec_builtins(data, data->table->commands[0].args);
			close_redirections(data, 0);
			restore_stdio(data);
			return (0);
		}
	}
	execution_loop(data);
	return (0);
}

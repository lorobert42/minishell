/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/05/03 13:57:11 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_access(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		fatal_error("is a directory", path, 126);
	}
	if (access(path, F_OK) != 0)
		fatal_error(NULL, path, 127);
	if (access(path, R_OK | X_OK) != 0)
		fatal_error(NULL, path, 126);
}

char	*find_path(t_data *data, int num)
{
	char	*env;

	if (ft_strchr(data->table->commands[num].args[0], '/'))
	{
		check_access(data->table->commands[num].args[0]);
		return (data->table->commands[num].args[0]);
	}
	env = ft_getenv(data->env, "PATH");
	if (env != NULL)
	{
		return (utils_path(data, env, num));
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
		if (!data->table->commands[i].args[0])
			exit(0);
		path = find_path(data, i);
		if (!path)
		{
			print_error("command not found", data->table->commands[i].args[0]);
			g_glob.nb_children--;
			exit(127);
		}
		termios_restore_ctrl();
		execve(path, data->table->commands[i].args, data->env);
	}
	exit(0);
}

void	execution_loop(t_data *data)
{
	pid_t	pid;
	int		i;
	int		status;

	pid = 0;
	i = 0;
	while (i < data->table->n_commands)
	{
		init_and_exec_children(data, i, pid);
		i++;
	}
	close_all_pipes(data, i - 1);
	while (g_glob.nb_children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
			g_glob.nb_children--;
	}
	i = -1;
	while (++i < data->table->n_commands)
		delete_heredoc(data, i);
	check_status(status);
	g_glob.status = 0;
	termios_remove_ctrl();
}

int	execute(t_data *data)
{
	if (set_heredoc(data))
		return (0);
	if (data->table->n_commands == 1)
	{
		if (is_builtins(data->table->commands[0].args))
		{
			return (inside_exec(data));
		}
	}
	execution_loop(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:27:20 by afavre            #+#    #+#             */
/*   Updated: 2023/05/10 15:12:09 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *path, char *cmd)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (cmd == NULL)
		res = ft_strdup(temp);
	else
		res = ft_strjoin(temp, cmd);
	free(temp);
	return (res);
}

int	inside_exec(t_data *data)
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

void	init_and_exec_children(t_data *data, int i)
{
	g_glob.status = 1;
	pipe(data->table->commands[i].fd);
	data->table->commands[i].pid = fork();
	if (data->table->commands[i].pid == -1)
	{
		g_glob.error = 1;
		return ;
	}
	g_glob.nb_children += 1;
	if (data->table->commands[i].pid == 0)
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
		close_all_pipes(data, i);
		children(data, i);
	}
}

void	check_status(int status)
{
	if (WIFEXITED(status))
	{
		g_glob.error = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		g_glob.error = 128 + WTERMSIG(status);
	}
	if (g_glob.error == 138)
		print_error("bus error: 10\n", "executer");
	if (g_glob.error == 139)
		print_error("segmentation fault: 11\n", "executer");
}

char	*utils_path(t_data *data, char *env, int num)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_split(env, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		path = get_path(paths[i], data->table->commands[num].args[0]);
		if (access(path, F_OK) == 0)
		{
			check_access(path);
			clear_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	clear_split(paths);
	return (NULL);
}

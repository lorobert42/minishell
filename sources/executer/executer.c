/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:04:43 by afavre            #+#    #+#             */
/*   Updated: 2023/04/21 13:31:58 by lorobert         ###   ########.fr       */
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

	/* if (redirection_in(data, i))
	{
		close_redirections(data, i);
		exit(1);
	}
	if (redirection_out(data, i, 0))
	{
		close_redirections(data, i);
		exit(1);
	} */
	if (is_builtins(data->table->commands[i].args))
		exec_builtins(data, data->table->commands[i].args);
	else
	{
		path = find_path(data, i);
		if (path != NULL)
		{
			execve(path, data->table->commands[i].args, data->env);
		}
		else
			ft_printf("🤷 Hérishell: %s: a pas trouver ... 🤷\n", \
				data->table->commands[i].args[0]);
	}
	// close_redirections(data, i);
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
		pipe(data->table->commands[i].fd);
		pid = fork();
		g_glob.nb_children += 1;
		if (pid == 0)
		{
			if (i > 0)
			{
				dup2(data->table->commands[i - 1].fd[0], STDIN_FILENO);
				if (close(data->table->commands[i - 1].fd[0]) == -1)
					print_error(NULL, "close1");
				if (close(data->table->commands[i - 1].fd[1]) == -1)
					print_error(NULL, "close2");
			}
			if (i < data->table->n_commands - 1)
			{
				if (close(data->table->commands[i].fd[0]) == -1)
					print_error(NULL, "close3");
				dup2(data->table->commands[i].fd[1], STDOUT_FILENO);
				if (close(data->table->commands[i].fd[1]) == -1)
					print_error(NULL, "close4");
			}
			children(data, i);
		}
		else
		{
			if (i > 0)
			{
				if (close(data->table->commands[i - 1].fd[0]) == -1)
					print_error(NULL, "close5");
				if (close(data->table->commands[i - 1].fd[1]) == -1)
					print_error(NULL, "close6");
			}
		}
		i++;
	}
	if (i > 0)
	{
		if (close(data->table->commands[i - 1].fd[0]) == -1)
			print_error(NULL, "close7");
		if (close(data->table->commands[i - 1].fd[1]) == -1)
			print_error(NULL, "close8");
	}
	while (g_glob.nb_children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			g_glob.nb_children--;
		}
	}
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
			if (redirection_in(data, 0))
			{
				close_redirections(data, 0);
				return (1);
			}
			if (redirection_out(data, 0, 1))
			{
				close_redirections(data, 0);
				return (1);
			}
			exec_builtins(data, data->table->commands[0].args);
			close_redirections(data, 0);
			return (0);
		}
	}
	execution_loop(data);
	return (0);
}

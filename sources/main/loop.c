/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/03/31 14:33:40 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_export(t_data *data, char **cmd)
{
	char	**split;
	int		res;

	if (!cmd[1])
	{
		ft_export(data, NULL, NULL);
		return (0);
	}
	split = ft_split(cmd[1], '=');
	if (split[0])
	{
		res = ft_export(data, split[0], split[1]);
		clear_split(split);
	}
	if (!split[0] || res != 0)
	{
		g_glob = 1;
		errno = EINVAL;
		perror(cmd[1]);
	}
	return (0);
}

int	check_builtins(t_data *data)
{
	char	**cmd;

	cmd = data->table->commands[0].args;
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		return (ft_cd(data, data->table->commands->args[1]));
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		return (ft_env(data->env));
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		return (run_export(data, cmd));
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (ft_unset(data, cmd[1]));
	else if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		return (ft_echo(cmd + 1));
	return (1);
}

void	loop(t_data *data)
{
	char	*buffer;

	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		add_history(buffer);
		data->token = lexer(buffer);
		if (!data->token)
		{
			free(buffer);
			continue ;
		}
		if (expander(data->token, data->env) == 1)
		{
			clean_tokens(data->token);
			free(buffer);
			continue ;
		}
		data->table = parser(data->token);
		if (!data->table)
		{
			clean_tokens(data->token);
			free(buffer);
			continue ;
		}
		print_command_table(data->table);
		if (check_builtins(data))
		{
			executer(data);
		}
		clean_tokens(data->token);
		clean_command_table(data->table);
		free(buffer);
	}
}

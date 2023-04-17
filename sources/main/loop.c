/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/04/17 17:25:36 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtins_out(t_data *data, int i)
{
	char	**cmd;

	cmd = data->table->commands[i].args;
	if (cmd[0] == NULL)
		return (1);
	else if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		return (ft_cd(data, cmd));
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] != NULL)
		return (ft_export(data, cmd[1]));
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (ft_unset(data, cmd[1]));
	return (1);
}

int	check_builtins_forks(t_data *data, int i)
{
	char	**cmd;

	cmd = data->table->commands[i].args;
	if (cmd[0] == NULL)
		return (1);
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		return (ft_env(data->env));
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] == NULL)
		return (print_export(data->env));
	else if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		return (ft_echo(cmd + 1));
	return (1);
}

void	loop(t_data *data)
{
	char				*buffer;

	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		if (!buffer)
			exit(0);
		add_history(buffer);
		data->token = lexer(buffer);
		if (!data->token)
		{
			clean_tokens(data->token);
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
			print_error("syntax error", "parsing");
			continue ;
		}
		execute(data);
		clean_tokens(data->token);
		clean_command_table(data->table);
		free(buffer);
	}
}

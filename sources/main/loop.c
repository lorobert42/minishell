/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/03/29 14:05:33 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_export(t_data *data, char **cmd)
{
	char	**split;

	split = ft_split(cmd[1], '=');
	if (split[0] && split[1])
	{
		ft_export(&data->env, split[0], split[1]);
		clear_split(split);
	}
	return (0);
}

int	check_builtins(t_data *data, char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		return (ft_cd(cmd[1], &data->env));
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		return (ft_env(data->env, 0));
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (ft_pwd(data->env));
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		return (run_export(data, cmd));
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (ft_unset(&data->env, cmd[1]));
	clear_split(cmd);
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
		expander(data->token, data->env);
		data->table = *parser(data->token);
		print_command_table(&data->table);
		if (check_builtins(data, buffer))
		{
			ft_printf("Execution\n");
		}
		free(buffer);
	}
}

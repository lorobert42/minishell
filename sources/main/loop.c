
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/03/02 10:53:38 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_builtins(t_data *data, char *str)
{
	char	**cmd;
	char	**split;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		ft_cd(cmd[1], &data->env);
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		ft_env(data->env, 0);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		ft_pwd(data->env);
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
	{
		split = ft_split(cmd[1], '=');
		ft_export(&data->env, split[0], split[1]);
		clear_split(split);
	}
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		ft_unset(&data->env, cmd[1]);
	clear_split(cmd);
}

void	loop(t_data *data)
{
	char	*buffer;

	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		add_history(buffer);
		data->token = lexer(buffer);
		data->table = *parser(data->token);
		check_builtins(data, buffer);
		free(buffer);
	}
}

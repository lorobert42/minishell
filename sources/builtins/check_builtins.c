/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:24:55 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/24 14:35:23 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtins(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	else if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_data *data, char **cmd)
{
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		return (ft_exit(cmd));
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		return (ft_cd(data, cmd));
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] != NULL)
		return (ft_export(data, cmd[1]));
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0 && cmd[1] == NULL)
		return (print_export(data->env));
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (ft_unset(data, cmd[1]));
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		return (ft_env(data->env));
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd[0], "echo\0", 5) == 0)
		return (ft_echo(cmd + 1));
	return (1);
}

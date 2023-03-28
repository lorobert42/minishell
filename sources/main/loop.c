
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

	cmd = ft_split(str, ' ');
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		exit(0);
	else if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
	{
		ft_cd(cmd[1], &data->env);
	}
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
	{
		ft_env(data->env, 0);
	}
}

void	loop(t_data *data)
{
	int i;
	int j;
	char	*buffer;

	i = 0;
	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		add_history(buffer);
		data->token = lexer(buffer);
		data->table = *parser(data->token);
		check_builtins(data, buffer);
		while (i < data->table.n_commands)
		{
			printf("IN: %s\nOUT: %s\n", data->table.commands[i].infile, data->table.commands[i].outfile);
			j = 0;
			while (data->table.commands[i].command[j] != NULL)
			{
				printf("%s ", data->table.commands[i].command[j]);
				j++;
			}
			printf("\n");
			i++;
		}
		free(buffer);
	}
}

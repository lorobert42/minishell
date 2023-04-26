/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/04/20 13:45:45 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	loop(t_data *data)
{
	char				*buffer;

	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		//buffer = readline("my shell");
		if (!buffer)
			exit(g_glob.error);
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

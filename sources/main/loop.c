/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/05/04 13:42:20 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_loop(t_data *data, char *buffer)
{
	if (!data->token)
	{
		clean_tokens(data->token);
		free(buffer);
		return (1);
	}
	if (expander(data->token, data->env) == 1)
	{
		clean_tokens(data->token);
		free(buffer);
		print_error("unclosed quotes", "expander");
		g_glob.error = 1;
		return (1);
	}
	data->table = parser(data->token);
	if (!data->table)
	{
		clean_tokens(data->token);
		free(buffer);
		fatal_error("Parser error", NULL, 258);
	}
	return (0);
}

void	loop(t_data *data)
{
	char				*buffer;

	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		if (!buffer)
			exit(g_glob.error);
		if (buffer[0] != '\0')
			add_history(buffer);
		data->token = lexer(buffer);
		if (setup_loop(data, buffer))
			continue ;
		clean_tokens(data->token);
		execute(data);
		clean_command_table(data->table);
		free(buffer);
	}
}

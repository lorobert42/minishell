/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:13:08 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 11:03:21 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	inline_arg(t_data *data, char **av)
{
	char	**arg_input;
	int		i;

	arg_input = ft_split(av[2], ';');
	if (!arg_input)
		exit(0);
	i = 0;
	while (arg_input[i])
	{
		data->token = lexer(arg_input[i]);
		if (setup_loop(data, arg_input[i]))
		{
			i++;
			continue ;
		}
		clean_tokens(data->token);
		execute(data);
		clean_command_table(data->table);
		free(arg_input[i]);
		i++;
	}
	exit(g_glob.error);
}

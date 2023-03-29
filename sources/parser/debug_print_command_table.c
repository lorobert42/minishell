/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_command_table.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:25:08 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/29 13:51:31 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_command_table(t_command_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->n_commands)
	{
		ft_printf("IN: %s\n", table->commands[i].infile);
		ft_printf("OUT: %s\n", table->commands[i].outfile);
		j = 0;
		while (table->commands[i].command[j] != NULL)
		{
			ft_printf("%s ", table->commands[i].command[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

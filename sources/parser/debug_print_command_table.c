/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_command_table.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:25:08 by lorobert          #+#    #+#             */
/*   Updated: 2023/04/24 15:03:14 by lorobert         ###   ########.fr       */
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
		if (table->commands[i].infiles)
		{
			ft_printf("IN: %s, mode: %d\n", table->commands[i].infiles->name, table->commands[i].infiles->append);
		}
		if (table->commands[i].outfiles)
			ft_printf("OUT: %s\n", table->commands[i].outfiles->name);
		j = 0;
		while (table->commands[i].args[j] != NULL)
		{
			ft_printf("%s ", table->commands[i].args[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

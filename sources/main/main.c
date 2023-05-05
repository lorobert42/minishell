/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:18:54 by afavre            #+#    #+#             */
/*   Updated: 2023/05/05 14:59:31 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	sig_handler(&data);
	termios_remove_ctrl();
	init(&data, env);
	if (ac == 3 && ft_strncmp(av[1], "-c", 3) == 0 && av[2])
		inline_arg(&data, av);
	loop(&data);
}

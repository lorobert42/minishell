/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:00 by afavre            #+#    #+#             */
/*   Updated: 2023/04/19 10:06:12 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init(t_data *data, char **env)
{
	g_glob.error = 0;
	g_glob.status = 0;
	g_glob.parsing = 0;
	data->run = 1;
	data->env = parse_env(env);
}

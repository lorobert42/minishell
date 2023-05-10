/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:00 by afavre            #+#    #+#             */
/*   Updated: 2023/05/08 19:08:05 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_global	g_glob;

void	init(t_data *data, char **env)
{
	g_glob.error = 0;
	g_glob.status = 0;
	g_glob.parsing = 0;
	g_glob.nb_children = 0;
	data->run = 1;
	data->env = parse_env(env);
}

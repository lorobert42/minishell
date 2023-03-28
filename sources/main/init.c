
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:35:00 by afavre            #+#    #+#             */
/*   Updated: 2023/02/24 11:34:11 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init(t_data *data, char **env)
{
	(void)env;
	data->run = 1;
	data->env = parse_env(env);
/*	data->cmd_lst = NULL;
	data->pwd = ft_strdup(getenv("PWD"));
	data->home = ft_strdup(getenv("HOME"));
	data->old_pwd = ft_strdup(data->pwd);*/
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:19:59 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/28 13:23:06 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
	{
		free(env->key);
		env->key = NULL;
	}
	if (env->value)
	{
		free(env->value);
		env->value = NULL;
	}
	env->next = NULL;
}

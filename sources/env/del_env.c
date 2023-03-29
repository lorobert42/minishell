/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:19:59 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/28 13:41:13 by lorobert         ###   ########.fr       */
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
	free(env);
}

void	del_all_env(t_env **env)
{
	t_env	*next;

	while (*env)
	{
		next = (*env)->next;
		del_env(*env);
	}
}

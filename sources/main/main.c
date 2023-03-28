/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:18:54 by afavre            #+#    #+#             */
/*   Updated: 2023/03/28 10:18:57 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int main(int ac, char **av, char **env)
{
	t_data data;
	(void)ac;
	(void)av;

	init(&data, env);
	loop(&data);
}
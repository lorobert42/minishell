
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:43:34 by afavre            #+#    #+#             */
/*   Updated: 2023/03/02 10:53:38 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void test_built(t_data *data, char *str)
{
	char **cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
	{
		ft_cd("sources", &data->env);
	}
	if (ft_strncmp(cmd[0], "env\0", 4) == 0)
	{
		ft_printf("pwd --> %s\n", ft_getenv(data->env, "PWD"));
	}
}

void	loop(t_data *data)
{
	char	*buffer;

	while (data->run)
	{
		buffer = readline("🦔 \e[34m Hérishell 🦔 => \e[39m");
		add_history(buffer);
		test_built(data, buffer);
		//parse(data, buffer);
	}
}
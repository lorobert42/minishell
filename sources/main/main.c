/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:18:54 by afavre            #+#    #+#             */
/*   Updated: 2023/03/28 13:40:58 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_printf("%d ----> %s\n", i, tab[i]);
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	t_data data;

	(void)ac;
	(void)av;
	data.env = parse_env(env);
	ft_export(&data, "ducom", "duconm");
	print_str_tab(data.env);
}

/*int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init(&data, env);
	//loop(&data);
//	del_all_env(&data.env);
}*/

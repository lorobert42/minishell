/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:42:27 by afavre            #+#    #+#             */
/*   Updated: 2023/03/02 12:42:36 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_lstsize(t_cmd *lst)
{
	int	res;

	res = 0;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		res++;
		lst = lst->next;
	}
	if (lst->next == NULL)
		res++;
	return (res);
}

void	clear_lst(t_data *data)
{
	int		i;
	t_cmd	*next;

	i = cmd_lstsize(data->cmd_lst);
	while (i > 0)
	{
		next = data->cmd_lst->next;
		free(data->cmd_lst->cmd);
		clear_split(data->cmd_lst->args);
		free(data->cmd_lst);
		data->cmd_lst = next;
		i--;
	}
	free(data->cmd_lst);
}

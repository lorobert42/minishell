/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:08:49 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/08 11:39:05 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_sign(char *nb)
{
	return (nb[0] == '+' || nb[0] == '-');
}

char	*copy_str(char *nb, int i, int sign)
{
	char	*new;
	int		j;

	new = ft_calloc(ft_strlen(nb) - i + sign + 1, sizeof(char));
	if (!new)
		fatal_error(NULL, "malloc", 1);
	if (sign)
		new[0] = nb[0];
	j = sign;
	while (nb[i])
	{
		new[j] = nb[i];
		i++;
		j++;
	}
	return (new);
}

char	*remove_zero(char *nb)
{
	char	*new;
	int		i;
	int		sign;

	sign = get_sign(nb);
	i = sign;
	while (nb[i] == '0')
		i++;
	if (i == (int)ft_strlen(nb))
	{
		free(nb);
		return (ft_strdup("0"));
	}
	new = copy_str(nb, i, sign);
	free(nb);
	return (new);
}

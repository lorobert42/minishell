/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uitoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:31:35 by afavre            #+#    #+#             */
/*   Updated: 2022/11/03 11:48:06 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_size_u(unsigned int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

void	ft_fill_res_u(int size, int offset, unsigned int n, char *res)
{
	while (size > offset)
	{
		res[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

char	*ft_uitoa(unsigned int n)
{
	int		offset;
	int		size;
	char	*res;

	offset = 0;
	size = ft_get_size_u(n);
	res = malloc(sizeof(char) * size + 1);
	if (!(res))
		return (0);
	ft_fill_res_u(size, offset, n, res);
	res[size] = '\0';
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selecteur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:03:18 by afavre            #+#    #+#             */
/*   Updated: 2022/11/04 07:21:47 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_data(char type, void *data)
{
	int	res;

	res = 0;
	if (type == 'c')
		res = cast_char((char) data);
	if (type == 's')
		res = cast_string((char *)data);
	if (type == 'p')
		res = cast_pointeur((unsigned long long)data);
	if (type == 'd')
		res = cast_integer(ft_itoa((int) data));
	if (type == 'i')
		res = cast_integer(ft_itoa((int) data));
	if (type == 'u')
		res = cast_undecimal(ft_uitoa((int)data));
	if (type == 'x')
		res = cast_hexa_min((unsigned int)data);
	if (type == 'X')
		res = cast_hexa_maj((unsigned int)data);
	if (type == '%')
		res = cast_percent();
	return (res);
}

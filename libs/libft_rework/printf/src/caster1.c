/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:47:12 by afavre            #+#    #+#             */
/*   Updated: 2022/11/04 07:36:52 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	cast_char(char data)
{
	int	res;

	res = ft_putchar(data);
	return (res);
}

int	cast_string(char *data)
{
	int	res;

	res = 0;
	if (data != NULL)
		res += ft_putstr(data);
	else
		res += ft_putstr("(null)");
	return (res);
}

int	cast_pointeur(unsigned long long data)
{
	int	res;

	res = ft_print_ptr(data);
	return (res);
}

int	cast_integer(char *data)
{
	int	res;

	res = 0;
	res += ft_putstr(data);
	free(data);
	return (res);
}

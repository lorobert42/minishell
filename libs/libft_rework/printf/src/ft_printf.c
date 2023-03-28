/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:22:59 by afavre            #+#    #+#             */
/*   Updated: 2022/11/04 08:48:10 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	al;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(al, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				res += print_data(str[i + 1], NULL);
			else
				res += print_data(str[i + 1], va_arg(al, void *));
			i++;
		}
		else
			res += ft_putchar(str[i]);
		i++;
	}
	va_end(al);
	return (res);
}

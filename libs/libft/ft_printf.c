/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 08:54:02 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/26 15:53:17 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

static int	parse_conversion(t_conversion *c)
{
	if (*(c->format) == 'c')
		return (ft_printf_char(c));
	else if (*(c->format) == 's')
		return (ft_printf_string(c));
	else if (*(c->format) == 'p')
		return (ft_printf_ptr(c));
	else if (*(c->format) == 'd' || *(c->format) == 'i')
		return (ft_printf_int(c));
	else if (*(c->format) == 'u')
		return (ft_printf_uint(c));
	else if (*(c->format) == 'x')
		return (ft_printf_hex(c, 0));
	else if (*(c->format) == 'X')
		return (ft_printf_hex(c, 1));
	else if (*(c->format) == '%')
		return (write(1, "%", 1));
	return (-1);
}

static int	parse_format(t_conversion *c)
{
	int	count;

	count = 0;
	if (*(c->format) != '%')
		count = write(1, c->format, 1);
	else
	{
		(c->format)++;
		count = parse_conversion(c);
	}
	(c->format)++;
	return (count);
}

static void	init_flags(t_conversion **c)
{
	(*c)->minus = 0;
	(*c)->zero = 0;
	(*c)->point = 0;
	(*c)->hash = 0;
	(*c)->space = 0;
	(*c)->plus = 0;
	(*c)->width = 0;
	(*c)->precision = 0;
	(*c)->specifier = 0;
}

int	ft_printf(const char *format, ...)
{
	int				count;
	int				value;
	t_conversion	*conversion;

	count = 0;
	conversion = malloc(sizeof(t_conversion));
	if (!conversion)
		return (-1);
	init_flags(&conversion);
	conversion->format = format;
	va_start(conversion->args, format);
	while (*(conversion->format))
	{
		value = parse_format(conversion);
		if (value < 0)
		{
			free(conversion);
			return (-1);
		}
		count += value;
	}
	va_end(conversion->args);
	free(conversion);
	return (count);
}

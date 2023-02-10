/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 09:11:50 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/26 16:03:26 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

int	ft_printf_ptr(t_conversion *c)
{
	unsigned long int	ptr;
	char				*s;
	int					count;

	ptr = va_arg(c->args, unsigned long int);
	if (!ptr)
		return (write(1, "0x0", 3));
	if (write(1, "0x", 2) < 0)
		return (-1);
	s = ft_itoa_hex_long(ptr, 0);
	if (!s)
		return (-1);
	count = write(1, s, ft_strlen(s));
	free(s);
	if (count >= 0)
		return (count + 2);
	return (-1);
}

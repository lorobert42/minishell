/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:59:07 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/21 15:17:48 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

static size_t	ft_len_nbr(unsigned long int n)
{
	size_t	radix;

	radix = 1;
	while (n >= 16)
	{
		radix++;
		n /= 16;
	}
	return (radix);
}

char	*ft_itoa_hex_long(unsigned long int n, int is_upp)
{
	size_t	len;
	char	*nbr;
	char	*base;

	if (is_upp)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = ft_len_nbr(n);
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len--] = '\0';
	while (len)
	{
		nbr[len] = base[n % 16];
		n /= 16;
		len--;
	}
	nbr[0] = base[n];
	return (nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:59:07 by lorobert          #+#    #+#             */
/*   Updated: 2022/10/21 17:10:53 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <limits.h>

static size_t	ft_len_nbr(unsigned int n)
{
	size_t	radix;

	radix = 1;
	while (n >= 10)
	{
		radix++;
		n /= 10;
	}
	return (radix);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	size_t		len;
	char		*nbr;

	len = ft_len_nbr(n);
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len--] = '\0';
	while (len)
	{
		nbr[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	nbr[0] = n + '0';
	return (nbr);
}

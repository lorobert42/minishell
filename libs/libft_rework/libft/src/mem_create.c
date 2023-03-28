/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:46:10 by afavre            #+#    #+#             */
/*   Updated: 2022/11/21 10:46:40 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *mem, size_t size)
{
	size_t	i;
	char	*res;

	i = 0;
	res = mem;
	while (i < size)
	{
		res[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		**res;

	res = malloc(nmemb * size);
	if (res == NULL)
		return ((void *)0);
	ft_bzero(res, (nmemb * size));
	return (res);
}

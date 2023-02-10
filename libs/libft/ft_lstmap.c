/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:35:40 by lorobert          #+#    #+#             */
/*   Updated: 2022/08/25 15:19:29 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*start;

	if (!lst)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (NULL);
	start = res;
	lst = lst->next;
	while (lst)
	{
		res->next = ft_lstnew(f(lst->content));
		if (!res->next)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		res = res->next;
		lst = lst->next;
	}
	return (start);
}

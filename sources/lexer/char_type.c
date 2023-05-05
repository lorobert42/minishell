/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:19:02 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/05 09:49:52 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	issep(int c)
{
	return (c == '<' || c == '>' || c == '|' || ft_isspace(c));
}

t_token_type	quote_type(char c)
{
	if (c == '"')
		return (DBL_QUOTE_STR);
	else if (c == '\'')
		return (QUOTE_STR);
	return (LITERAL);
}

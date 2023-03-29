/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:36:13 by lorobert          #+#    #+#             */
/*   Updated: 2023/03/29 09:38:03 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir(t_token_type t)
{
	return (t == REDIR_LEFT || t == REDIR_RIGHT \
		|| t == REDIR_APPEND || t == HERE_DOC);
}

int	is_string(t_token_type t)
{
	return (t == LITERAL || t == QUOTE_STR || t == DBL_QUOTE_STR);
}

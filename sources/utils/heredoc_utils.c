/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorobert <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:26:54 by lorobert          #+#    #+#             */
/*   Updated: 2023/05/10 12:27:24 by lorobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_child(char **delim, int fd, int expand, t_data *data)
{
	sig_restore(data);
	heredoc_handler();
	heredoc_loop(data, delim, expand, fd);
	exit(0);
}

void	heredoc_parent(pid_t pid, t_data *data)
{
	sig_ignore();
	waitpid(pid, NULL, 0);
	sig_handler(data);
}

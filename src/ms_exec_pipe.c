/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:01:43 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/24 17:11:41 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe_close(int fd[2]);
void	ms_pipe_copy(int dest[2], int src[2]);
int		ms_pipe_last_fd(t_fd *fd_lst);

void	ms_pipe_close(int fd[2])
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}

void	ms_pipe_copy(int dest[2], int src[2])
{
	dest[0] = src[0];
	dest[1] = src[1];
}

int	ms_pipe_last_fd(t_fd *fd_lst)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = -1;
	while (fd_lst[i].path != NULL)
	{
		fd = fd_lst[i].fd;
		i++;
	}
	return (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:01:43 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/24 17:47:32 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe_close(int fd[2]);
void	ms_pipe_copy(int dest[2], int src[2]);
int		ms_pipe_last_fd(t_fd *fd_lst);
void	ms_pipe_close_all_cmd(t_cmd *cmd);
void	ms_pipe_close_fds(t_fd *fd);

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

void	ms_pipe_close_all_cmd(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur != NULL)
	{
		ms_pipe_close_fds(cmd->input);
		ms_pipe_close_fds(cmd->output);
		cur = cur->next;
	}
}

void	ms_pipe_close_fds(t_fd *fd)
{
	size_t	i;

	i = 0;
	while (fd[i].path != NULL)
	{
		if (fd[i].fd >= 0)
			close(fd[i].fd);
		i++;
	}
}
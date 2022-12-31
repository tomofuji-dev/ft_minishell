/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:01:43 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 16:41:33 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_fd_close(int fd[2]);
void		ms_fd_copy(int dest[2], int src[2]);
int			ms_fd_last_fd(t_fd *fd_lst);
void		ms_fd_close_all_cmd(t_cmd *cmd);
static void	ms_fd_close_fds(t_fd *fd);

void	ms_fd_close(int fd[2])
{
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

void	ms_fd_copy(int dest[2], int src[2])
{
	dest[0] = src[0];
	dest[1] = src[1];
}

int	ms_fd_last_fd(t_fd *fd_lst)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = INVALID_FILENO;
	while (fd_lst[i].path != NULL)
	{
		fd = fd_lst[i].fd;
		i++;
	}
	return (fd);
}

void	ms_fd_close_all_cmd(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur != NULL)
	{
		ms_fd_close_fds(cur->input);
		ms_fd_close_fds(cur->output);
		cur = cur->next;
	}
}

void	ms_fd_close_fds(t_fd *fd)
{
	size_t	i;

	i = 0;
	while (fd[i].path != NULL)
	{
		if (fd[i].fd > STDERR_FILENO)
			close(fd[i].fd);
		i++;
	}
}

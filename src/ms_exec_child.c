/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/20 14:18:59 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_in_child_process(t_cmd *cmd);
void	ms_exec_a_cmd(t_cmd *cmd, int prev_pipe[2], int now_pipe[2]);
void	ms_close_pipe(int fd[2]);
void	ms_copy_pipe(int dest[2], int src[2]);
void	ms_wait_all(t_cmd *cmd_lst);

void	ms_exec_in_child_process(t_cmd *cmd)
{
	int		prev_pipe[2];
	int		now_pipe[2];
	t_cmd	*now_cmd;

	prev_pipe[0] = 0;
	prev_pipe[1] = 1;
	now_cmd = cmd;
	while (now_cmd != NULL)
	{
		pipe(now_pipe);
		ms_exec_a_cmd(now_cmd, prev_pipe, now_pipe);
		ms_close_pipe(prev_pipe);
		ms_copy_pipe(prev_pipe, now_pipe);
		now_cmd = now_cmd->next;
	}
	return (ms_wait_all(cmd));
}

void	ms_exec_a_cmd(t_cmd *cmd, int prev_pipe[2], int now_pipe[2])
{
	int		fd[2];

	fd[0] = prev_pipe[0];
	fd[1] = now_pipe[1];
	if (cmd->input >= 0)
		fd[0] = cmd->input->fd;
	if (cmd->output >= 0)
		fd[1] = cmd->output->fd;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		ms_close_pipe(fd);
		ms_close_pipe(prev_pipe);
		ms_close_pipe(now_pipe);
		execve(cmd->path, cmd->arg, g_shell->environ);
	}
	else
		return ;
}

void	ms_close_pipe(int fd[2])
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}

void	ms_copy_pipe(int dest[2], int src[2])
{
	dest[0] = src[0];
	dest[1] = src[1];
}

void	ms_wait_all(t_cmd *cmd_lst)
{
	int		status;
	t_cmd	*now_cmd;

	now_cmd = cmd_lst;
	while (now_cmd != NULL)
	{
		waitpid(now_cmd->pid, &status, 1);
		now_cmd = now_cmd->next;
	}
	g_shell->status = status;
	return ;
}
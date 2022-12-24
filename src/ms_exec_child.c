/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/24 17:51:27 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_in_child_process(t_cmd *cmd);
void	\
ms_exec_a_cmd(t_cmd *cmd, int prev_pipe[2], int now_pipe[2], char **envp);
void	ms_wait_all(t_cmd *cmd_lst);

void	ms_exec_in_child_process(t_cmd *cmd)
{
	int		prev_pipe[2];
	int		now_pipe[2];
	t_cmd	*now_cmd;
	char	**envp;

	envp = ms_lst2map(&g_shell.environ);
	if (envp == NULL)
		return ;
	prev_pipe[0] = 0;
	prev_pipe[1] = 1;
	now_cmd = cmd;
	while (now_cmd != NULL)
	{
		pipe(now_pipe);
		ms_exec_a_cmd(now_cmd, prev_pipe, now_pipe, envp);
		ms_pipe_close(prev_pipe);
		ms_pipe_copy(prev_pipe, now_pipe);
		now_cmd = now_cmd->next;
	}
	free(envp);
	return (ms_wait_all(cmd));
}

void	\
	ms_exec_a_cmd(t_cmd *cmd, int prev_pipe[2], int now_pipe[2], char **envp)
{
	int		fd[2];

	fd[0] = prev_pipe[0];
	fd[1] = now_pipe[1];
	if (ms_pipe_last_fd(cmd->input) > 0)
		fd[0] = cmd->input->fd;
	if (ms_pipe_last_fd(cmd->output) > 0)
		fd[1] = cmd->output->fd;
	printf("fd[0]: %d, fd[1] %d\n", fd[0], fd[1]);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		ms_pipe_close(fd);
		ms_pipe_close(prev_pipe);
		ms_pipe_close(now_pipe);
		execve(cmd->path, cmd->arg, envp);
	}
	else
		return ;
}

void	ms_wait_all(t_cmd *cmd_lst)
{
	int		status;
	t_cmd	*now_cmd;

	now_cmd = cmd_lst;
	while (now_cmd != NULL)
	{
		waitpid(now_cmd->pid, &status, 0);
		now_cmd = now_cmd->next;
	}
	g_shell.status = status;
	return ;
}

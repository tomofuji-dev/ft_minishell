/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/27 14:24:56 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_in_child_process(t_cmd *cmd);
void	\
ms_exec_a_cmd(t_cmd *cmd, int prev_pipe[2], int now_pipe[2], char **envp);
void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp);
void	ms_wait_all(t_cmd *cmd_lst);
void	ms_handle_status(int status);

void	ms_exec_in_child_process(t_cmd *cmd)
{
	int		prev_pipe[2];
	int		now_pipe[2];
	t_cmd	*now_cmd;
	char	**envp;

	envp = ms_lst2map(g_shell.environ);
	if (envp == NULL)
		return ;
	ms_init_fd(prev_pipe);
	now_cmd = cmd;
	while (now_cmd != NULL)
	{
		if (now_cmd->next != NULL)
			pipe(now_pipe);
		else
			ms_init_fd(now_pipe);
		ms_exec_a_cmd(now_cmd, prev_pipe, now_pipe, envp);
		ms_fd_close(prev_pipe);
		ms_fd_copy(prev_pipe, now_pipe);
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
	if (ms_fd_last_fd(cmd->input) > 0)
		fd[0] = ms_fd_last_fd(cmd->input);
	if (ms_fd_last_fd(cmd->output) > 0)
		fd[1] = ms_fd_last_fd(cmd->output);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		ms_fd_close(fd);
		ms_fd_close(prev_pipe);
		ms_fd_close(now_pipe);
		ms_exec_a_cmd_sub(cmd, envp);
	}
}

void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp)
{
	int		(*builtin)(char *arg[]);

	if (cmd->path[0] == '\0')
	{
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	if (ms_is_directory(cmd->path))
	{
		ft_putendl_fd("Is a directory", 2);
		exit(127);
	}
	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL)
		exit(builtin(cmd->arg));
	else
	{
		errno = 0;
		execve(cmd->path, cmd->arg, envp);
		ft_putendl_fd(strerror(errno), 2);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
}

void	ms_wait_all(t_cmd *cmd_lst)
{
	int		status;
	t_cmd	*now_cmd;

	now_cmd = cmd_lst;
	while (now_cmd != NULL)
	{
		waitpid(now_cmd->pid, &status, 0);
		ms_handle_status(status);
		now_cmd = now_cmd->next;
	}
	ms_fd_close_all_cmd(cmd_lst);
	return ;
}

void	ms_handle_status(int status)
{
	if (WIFEXITED(status))
		g_shell.status = WEXITSTATUS(status);
	else
		return ;
}

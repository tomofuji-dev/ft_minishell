/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/01 20:37:17 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_exec_in_child_process(t_cmd *cmd);
static void	ms_exec_a_cmd(t_cmd *cmd, \
	int prev_pipe[2], int now_pipe[2], char **envp);
static void	ms_exec_a_cmd_sub(t_cmd *cmd, char **envp);
static void	ms_wait_all(t_cmd *cmd_lst);
static void	ms_handle_status(int status);

void	ms_exec_in_child_process(t_cmd *cmd)
{
	int		prev_pipe[2];
	int		now_pipe[2];
	t_cmd	*now_cmd;
	char	**envp;

	envp = ms_map_lst2map(g_shell.environ);
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
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
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
		ft_putendl_fd(MSG_NO_CMD, STDERR_FILENO);
		exit(STATUS_NO_CMD);
	}
	if (ms_is_directory(cmd->path))
	{
		ft_putendl_fd(MSG_ISDIR, STDERR_FILENO);
		exit(STATUS_NOT_EXEC);
	}
	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL)
		exit(builtin(cmd->arg));
	else
	{
		errno = ERR_NOERR;
		execve(cmd->path, cmd->arg, envp);
		if (errno != ERR_NOERR)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		if (errno == ENOENT)
			exit(STATUS_NO_CMD);
		exit(STATUS_NOT_EXEC);
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
	g_shell.kill_child = false;
	ms_fd_close_all_cmd(cmd_lst);
	return ;
}

void	ms_handle_status(int status)
{
	if (WIFEXITED(status) && g_shell.kill_child == false)
		g_shell.status = WEXITSTATUS(status);
	else
		return ;
}

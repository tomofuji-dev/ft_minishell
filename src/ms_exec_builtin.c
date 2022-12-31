/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 12:24:37 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[]))
{
	int	tmp_fd[2];
	int	use_fd[2];

	tmp_fd[0] = dup(0);
	tmp_fd[1] = dup(1);
	use_fd[0] = ms_fd_last_fd(cmd->input);
	use_fd[1] = ms_fd_last_fd(cmd->output);
	if (use_fd[0] > 0)
		dup2(use_fd[0], 0);
	if (use_fd[1] >= 0 && use_fd[1] != 1)
		dup2(use_fd[1], 1);
	g_shell.status = builtin(cmd->arg);
	ms_fd_close_all_cmd(cmd);
	dup2(tmp_fd[0], 0);
	dup2(tmp_fd[1], 1);
	ms_fd_close(tmp_fd);
}

int	(*ms_builtin_getfunc(char *arg))(char *argv[])
{
	if (ft_strcmp(arg, "echo") == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(arg, "cd") == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(arg, "pwd") == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(arg, "export") == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(arg, "unset") == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(arg, "env") == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(arg, "exit") == 0)
		return (ms_builtin_exit);
	return (NULL);
}

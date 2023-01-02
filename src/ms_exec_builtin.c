/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/01 20:49:33 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[]))
{
	int	tmp_fd[2];
	int	use_fd[2];

	tmp_fd[0] = dup(STDIN_FILENO);
	tmp_fd[1] = dup(STDOUT_FILENO);
	use_fd[0] = ms_fd_last_fd(cmd->input);
	use_fd[1] = ms_fd_last_fd(cmd->output);
	if (use_fd[0] > STDIN_FILENO)
		dup2(use_fd[0], STDIN_FILENO);
	if (use_fd[1] >= STDIN_FILENO && use_fd[1] != STDOUT_FILENO)
		dup2(use_fd[1], STDOUT_FILENO);
	g_shell.status = builtin(cmd->arg);
	ms_fd_close_all_cmd(cmd);
	dup2(tmp_fd[0], STDIN_FILENO);
	dup2(tmp_fd[1], STDOUT_FILENO);
	ms_fd_close(tmp_fd);
}

int	(*ms_builtin_getfunc(char *arg))(char *argv[])
{
	if (ft_strcmp(arg, CMD_ECHO) == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(arg, CMD_CD) == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(arg, CMD_PWD) == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(arg, CMD_EXPORT) == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(arg, CMD_UNSET) == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(arg, CMD_ENV) == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(arg, CMD_EXIT) == 0)
		return (ms_builtin_exit);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:38:39 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/24 18:48:14 by Yoshihiro K      ###   ########.fr       */
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
}

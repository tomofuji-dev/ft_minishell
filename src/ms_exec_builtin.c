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

void	ms_exec_a_builtin(t_cmd *cmd, int (*builtin)(char *arg[]))
{
	g_shell.status = builtin(cmd->arg);
}

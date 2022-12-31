/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:45:16 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 14:45:46 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ms_exec(t_cmd *cmd);
static int	ms_cmdsize(t_cmd *cmd);

void	ms_exec(t_cmd *cmd)
{
	int	(*builtin)(char *arg[]);

	if (cmd == NULL)
		return ;
	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL && ms_cmdsize(cmd) == 1)
		ms_exec_a_builtin(cmd, builtin);
	else
		ms_exec_in_child_process(cmd);
	ms_clear_cmd_and_return_null(cmd);
}

static int	ms_cmdsize(t_cmd *cmd)
{
	int	size;

	size = 0;
	while (cmd != NULL)
	{
		size++;
		cmd = cmd->next;
	}
	return (size);
}
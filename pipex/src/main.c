/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:17:50 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/02 16:10:59 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "constant.h"

//int	pp_exec(char *file1, char *cmd, char *envp[])
void	pp_exec_cmd(t_cmd *cmd)
{
	
}

int	pp_exec_cmds(t_cmd *cmd)
{
	t_cmd	*now_cmd;

	now_cmd = cmd;
	while (now_cmd != NULL)
	{
		pp_exec_cmd(now_cmd);
		now_cmd = now_cmd->next;
	}
	pp_wait_cmds(cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		errnum;
	t_cmd	*cmd_lst;

	if (pp_check_argc(argc) == false)
		return (ARGC_ERR);
	cmd_lst = pp_args_to_cmdlst(argc, argv, envp);
	errnum = pp_exec(cmd_lst);
	pp_clear_cmdlst(cmd_lst, argc - 2);
	return (errnum);
}

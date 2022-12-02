/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:17:50 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/02 15:04:25 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "constant.h"

//int	pp_exec(char *file1, char *cmd, char *envp[])
int	pp_exec(t_cmd *cmd)
{
	int		errnum;

	errnum = execve(cmd->cmd_path, cmd->cmd_split, cmd->envp);
	return (errnum);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		errnum;
	t_cmd	*cmd_lst;
	t_cmd	*now_cmd;

	if (pp_check_argc(argc) == false)
		return (ARGC_ERR);
	cmd_lst = pp_args_to_cmdlst(argc, argv, envp);
	errnum = 0;
	now_cmd = cmd_lst;
	while (now_cmd != NULL && errnum == 0)
	{
		errnum = pp_exec(cmd_lst);
		now_cmd = now_cmd->next;
	}
	pp_clear_cmdlst(cmd_lst, argc - 2);
	return (errnum);
}

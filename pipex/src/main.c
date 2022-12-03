/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:17:50 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/03 16:01:26 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "constant.h"

int	pp_exec(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (cmd->next == NULL)
		execve(cmd->cmd_path, cmd->cmd_split, cmd->envp);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		pp_exec(cmd->next);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execve(cmd->cmd_path, cmd->cmd_split, cmd->envp);
	}
	return (0);
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

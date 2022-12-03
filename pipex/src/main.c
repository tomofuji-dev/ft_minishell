/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:17:50 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/03 16:15:21 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "constant.h"

int	pp_exec(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (cmd->next == NULL)
	{
		dup2(cmd->out_fd, 1);
		execve(cmd->cmd_path, cmd->cmd_split, cmd->envp);
	}
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
		if (cmd->prev == NULL)
			dup2(cmd->in_fd, 0);
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
	pp_file_open(argc, argv, cmd_lst);
	errnum = pp_exec(cmd_lst);
	pp_clear_cmdlst(cmd_lst, argc - 2);
	pp_file_close(cmd_lst);
	return (errnum);
}

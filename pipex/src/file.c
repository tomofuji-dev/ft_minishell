/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/03 16:31:33 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "constant.h"

void	pp_file_open(int argc, char *argv[], t_cmd *cmd)
{
	cmd->in_fd = open(argv[1], O_RDONLY);
	if (cmd->in_fd == -1)
		exit (FILE_OPEN_ERR);
	while (cmd->next != NULL)
		cmd = cmd->next;
	cmd->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (cmd->out_fd == -1)
		exit (FILE_OPEN_ERR);
}

void	pp_file_close(t_cmd *cmd)
{
	close(cmd->in_fd);
	close(cmd->out_fd);
}

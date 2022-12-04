/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/04 15:44:27 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "constant.h"

void	pp_file_open(int argc, char *argv[], t_cmd *cmd)
{
	int	fd[2];

	if (ft_strncmp(argv[1], "here_doc", HEREDOC_LEN))
		cmd->in_fd = open(argv[1], O_RDONLY);
	else
	{
		pipe(fd);
		cmd->in_fd = fd[0];
		ft_putstr_fd("this", fd[1]);
		// ft_putstr_fd(get_heredoc_txt(argv[2]), fd[1]);
		close(fd[1]);
	}
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

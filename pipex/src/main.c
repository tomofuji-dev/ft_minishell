/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:17:50 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/01 13:57:00 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//int	pp_exec(char *file1, char *cmd, char *envp[])
int	pp_exec(char *cmd, char *envp[])
{
	char	**cmd_split;
	int		errnum;

	cmd_split = ft_split(cmd, ' ');
	errnum = execve(cmd_split[0], cmd_split, envp);
	free(cmd_split);
	return (errnum);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		errnum;
	(void) argv;
	if (check_argc(argc) == false)
		return (1);
	errnum = pp_exec(argv[2], envp);
	return (errnum);
}

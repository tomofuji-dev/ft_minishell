/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 14:31:43 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_exit(char *argv[])
{
	int	status;

	ft_putendl_fd(MSG_EXIT, STDOUT_FILENO);
	if (argv == NULL || argv[0] == NULL || argv[1] == NULL)
		status = g_shell.status;
	else if (argv[2] == NULL)
	{
		if (ms_strisdigit(argv[1]))
			status = ft_atoi(argv[1]);
		else
		{
			ft_putendl_fd(MSG_ARG_NOTNUM, STDERR_FILENO);
			status = STATUS_MASK;
		}
	}
	else
	{
		ft_putendl_fd(MSG_ARG_MANY, STDERR_FILENO);
		return (STATUS_FAILURE);
	}
	exit(status);
}

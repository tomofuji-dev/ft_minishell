/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/26 22:06:42 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_exit(char *argv[])
{
	int	status;

	printf("%s\n", MSG_EXIT);
	if (argv[1] == NULL)
		status = g_shell.status;
	else if (argv[2] == NULL)
	{
		if (ms_strisdigit(argv[1]))
			status = ft_atoi(argv[1]);
		else
		{
			ft_putendl_fd("numeric argument required", 2);
			status = 0xff;
		}
	}
	else
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	exit(status);
}

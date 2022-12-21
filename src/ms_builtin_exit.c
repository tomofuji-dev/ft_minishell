/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/19 15:39:26 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_exit(char *argv[])
{
	int	status;

	printf("%s\n", MSG_EXIT);
	if (argv[1] == NULL)
		status = g_shell.status;
	else
		status = ft_atoi(argv[1]);
	exit(status);
}

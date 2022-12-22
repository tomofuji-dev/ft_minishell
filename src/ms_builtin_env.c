/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:39:36 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/22 14:59:59 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_env(char *argv[])
{
	t_list	*cur;

	if (argv == NULL)
		return (0);
	cur = g_shell.environ;
	while (g_shell.environ != NULL)
		ft_putendl_fd(g_shell.environ[i], STDOUT);
	return (0);
}

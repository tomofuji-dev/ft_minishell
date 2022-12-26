/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:39:36 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/26 15:10:00 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_env(char *argv[])
{
	t_list	*cur;

	if (argv == NULL)
		return (0);
	cur = g_shell.environ;
	while (cur != NULL)
	{
		ft_putendl_fd(cur->content, STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}

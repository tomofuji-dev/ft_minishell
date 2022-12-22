/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:39:36 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/22 10:40:35 by Yoshihiro K      ###   ########.fr       */
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
		ft_putendl_fd(cur->content, STDOUT);
		cur = cur->next;
	}
	return (0);
}

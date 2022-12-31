/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/23 06:22:30 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*ms_builtin_getfunc(char *arg))(char *argv[])
{
	if (ft_strcmp(arg, "echo") == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(arg, "cd") == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(arg, "pwd") == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(arg, "export") == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(arg, "unset") == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(arg, "env") == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(arg, "exit") == 0)
		return (ms_builtin_exit);
	return (NULL);
}

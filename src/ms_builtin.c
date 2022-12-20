/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/20 14:27:01 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*ms_builtin_getfunc(char *arg))(char *argv[])
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (ms_builtin_exit);
	return (NULL);
}

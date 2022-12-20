/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/20 11:01:16 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	(*ms_get_builtin(char *arg[]))(char *)
{
	if (ft_strcmp(arg[0], "echo") == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(arg[0], "cd") == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(arg[0], "export") == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(arg[0], "env") == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (ms_builtin_exit);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	(void *) buitin;

	if (argc <= 1)
		return (1);
	builtin = ms_isbuiltin(&argv[1]);
	if (builtin)
		builtin(&argv[1]);
	return (0);
}

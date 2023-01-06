/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2023/01/06 20:29:57 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_pwd(char *argv[])
{
	char	cwd[PATH_MAX + 1];
	char	*pwd;

	if (argv == NULL)
		return (0);
	errno = 0;
	getcwd(cwd, PATH_MAX);
	pwd = ms_getenv_val(ENV_PWD);
	if (pwd != NULL && ft_strcmp(cwd, pwd + 1) == 0)
		ft_strlcpy(cwd, pwd, PATH_MAX + 1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (errno);
}

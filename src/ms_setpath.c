/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2023/01/10 02:22:42 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_setpath_home(char *path, char *arg);
void	ms_setpath_absolute(char *path, char *arg);
void	ms_setpath_relative(char *path, char *arg);

void	ms_setpath_home(char *path, char *arg)
{
	ft_strlcpy(path, ms_getenv_val(ENV_HOME), PATH_MAX + 1);
	ft_strlcat(path, &arg[1], PATH_MAX + 1);
}

void	ms_setpath_absolute(char *path, char *arg)
{
	ft_strlcpy(path, arg, PATH_MAX + 1);
}

void	ms_setpath_relative(char *path, char *arg)
{
	char	*pwd;
	char	cwd[PATH_MAX + 1];

	pwd = ms_getenv_val(ENV_PWD);
	if (pwd == NULL)
		ft_strlcpy(path, getcwd(cwd, PATH_MAX), PATH_MAX + 1);
	else
		ft_strlcpy(path, pwd, PATH_MAX + 1);
	if (path[1] != '\0' && path[1] != CHR_DIR)
		ft_strlcat(path, STR_DIR, PATH_MAX + 1);
	ft_strlcat(path, arg, PATH_MAX + 1);
}

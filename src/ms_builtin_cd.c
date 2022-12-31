/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 12:18:10 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_cd(char *argv[]);
int	ms_builtin_cd_chdir(char *path);
int	ms_builtin_cd_export(char *key, char *val);

int	ms_builtin_cd(char	*argv[])
{
	char	path[PATH_MAX + 1];
	int		status;

	if (argv == NULL || argv[1] == NULL)
		return (ms_builtin_cd_chdir(ms_getenv_val(ENV_HOME)));
	else if (argv[1][0] == CHR_HOME \
		&& (argv[1][1] == CHR_DIR || argv[1][1] == '\0'))
		ms_setpath_home(path, argv[1]);
	else if (!ft_strncmp(argv[1], "-", PATH_MAX + 1))
		return (ms_builtin_cd_chdir(ms_getenv_val("OLDPWD")));
	else if (argv[1][0] == CHR_DIR)
		ms_setpath_absolute(path, argv[1]);
	else
		ms_setpath_relative(path, argv[1]);
	status = ms_builtin_cd_chdir(path);
	return (status);
}

int	ms_builtin_cd_chdir(char *path)
{
	if (path == NULL)
	{
		ft_putendl_fd("OLDPWD not set", 2);
		return (1);
	}
	else if (chdir(path))
	{
		ft_putendl_fd("No such file or directory", 2);
		return (1);
	}
	ms_builtin_cd_export(ENV_OLDPWD, ms_getenv_val(ENV_PWD));
	ms_builtin_cd_export(ENV_PWD, getcwd(path, PATH_MAX));
	return (0);
}

int	ms_builtin_cd_export(char *key, char *val)
{
	char	*keyval;
	size_t	len;

	if (key == NULL || val == NULL)
		return (1);
	len = ft_strlen(key) + 1;
	keyval = (char *)malloc((len + ft_strlen(val) + 1) * sizeof(char));
	if (keyval == NULL)
		return (errno);
	ft_strlcpy(keyval, key, len);
	ft_strlcpy(keyval + len, val, ft_strlen(val) + 1);
	ms_search_env_and_set(keyval);
	free(keyval);
	return (0);
}

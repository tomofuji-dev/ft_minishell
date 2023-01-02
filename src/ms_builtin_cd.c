/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2023/01/02 19:18:27 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ms_builtin_cd(char *argv[]);
static int	ms_builtin_cd_env(char	*key);
static int	ms_builtin_cd_chdir(char *path);
static int	ms_builtin_cd_export(char *key, char *val);

int	ms_builtin_cd(char	*argv[])
{
	char	path[PATH_MAX + 1];
	int		status;

	if (argv == NULL || argv[1] == NULL)
		return (ms_builtin_cd_env(ENV_HOME));
	else if (argv[1][0] == CHR_HOME \
		&& (argv[1][1] == CHR_DIR || argv[1][1] == '\0'))
	{
		if (ms_getenv_val(ENV_HOME) == NULL)
			return (ms_builtin_cd_env(ENV_HOME));
		ms_setpath_home(path, argv[1]);
	}
	else if (ft_strcmp(argv[1], STR_OLDPWD) == 0)
		return (ms_builtin_cd_env(ENV_OLDPWD));
	else if (argv[1][0] == CHR_DIR)
		ms_setpath_absolute(path, argv[1]);
	else
		ms_setpath_relative(path, argv[1]);
	status = ms_builtin_cd_chdir(path);
	return (status);
}

static int	ms_builtin_cd_env(char	*key)
{
	char	*val;

	val = ms_getenv_val(key);
	if (val)
		return (ms_builtin_cd_chdir(val));
	else if (ft_strcmp(key, ENV_HOME) == 0)
		ft_putendl_fd(MSG_NO_HOME, STDERR_FILENO);
	else if (ft_strcmp(key, ENV_OLDPWD) == 0)
		ft_putendl_fd(MSG_NO_OLDPWD, STDERR_FILENO);
	else
		return (ms_builtin_cd_chdir(NULL));
	return (STATUS_FAILURE);
}

static int	ms_builtin_cd_chdir(char *path)
{
	if (path == NULL || chdir(path))
	{
		ft_putendl_fd(MSG_ENOENT, STDERR_FILENO);
		return (STATUS_FAILURE);
	}
	ms_builtin_cd_export(ENV_OLDPWD, ms_getenv_val(ENV_PWD));
	ms_builtin_cd_export(ENV_PWD, getcwd(path, PATH_MAX));
	return (STATUS_SUCCESS);
}

static int	ms_builtin_cd_export(char *key, char *val)
{
	char	*keyval;
	size_t	len;

	if (key == NULL || val == NULL)
		return (STATUS_FAILURE);
	len = ft_strlen(key) + 1;
	keyval = (char *)malloc((len + ft_strlen(val) + 1) * sizeof(char));
	if (keyval == NULL)
		return (errno);
	ft_strlcpy(keyval, key, len);
	ft_strlcpy(keyval + len, val, ft_strlen(val) + 1);
	ms_search_env_and_set(keyval);
	free(keyval);
	return (STATUS_SUCCESS);
}

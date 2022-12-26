/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:11:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/26 12:06:41 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHR_DIR		'/'
#define ENV_PWD		"PWD"
#define ENV_PATH	"PATH"

char	*ms_getpath_cmd(char *name);
char	*ms_getpath_relative(char *name);
char	*ms_getpath_envpath(char *name);
char	*ms_getpath_join(char *dirpath, char *name);

char	*ms_getpath_cmd(char *name)
{
	if (name == NULL)
		return (NULL);
	if (ms_builtin_getfunc(name))
		return (ft_strdup(name));
	else if (*name == CHR_DIR)
		return (ft_strdup(name));
	else if (ft_strchr(name, CHR_DIR))
		return (ms_getpath_relative(name));
	return (ms_getpath_envpath(name));
}

char	*ms_getpath_relative(char *name)
{
	char	*path;
	char	*pwd;

	pwd = ft_strdup(getenv(ENV_PWD));
	if (pwd == NULL)
		return (NULL);
	path = ms_getpath_join(pwd, name);
	free(pwd);
	return (path);
}

char	*ms_getpath_envpath(char *name)
{
	char		*cmdpath;
	char		*envpath;
	char		**envpath_split;
	struct stat	stat_buf;

	envpath = getenv(ENV_PATH);
	envpath_split = ft_split(envpath, ':');
	if (envpath_split == NULL)
		return (NULL);
	while (*envpath_split)
	{
		cmdpath = ms_getpath_join(*envpath_split, name);
		if (cmdpath == NULL)
			return (NULL);
		stat(cmdpath, &stat_buf);
		if ((stat_buf.st_mode & S_IFMT) == S_IFREG)
			return (cmdpath);
		envpath_split++;
	}
	return (NULL);
}

char	*ms_getpath_join(char *dirpath, char *name)
{
	char	*path;
	size_t	len_dir;
	size_t	len_name;

	len_dir = ft_strlen(dirpath);
	len_name = ft_strlen(name);
	path = (char *)malloc((len_dir + len_name + 2) * sizeof(char));
	if (path == NULL)
		return (NULL);
	ft_strlcpy(path, dirpath, len_dir + 1);
	*(path + len_dir) = CHR_DIR;
	ft_strlcpy(path + len_dir + 1, name, len_name + 1);
	return (path);
}

/*
bool	ms_getpath_test(char *envpath, char *name)
{
	char	path[MAX_PATH + 1];

	ft_strlcpy(path, *envpath, MAX_PATH + 1);
	// todo: over 1024 case
	// todo: continue when return NULL
	ft_strlcat(path, "/", MAX_PATH + 1);
	ft_strlcat(path, name, MAX_PATH + 1);
	if (access(path, X_OK) == 0)
		return (true);
	return (false);
}
*/

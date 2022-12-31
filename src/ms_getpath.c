/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:11:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 12:19:59 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHR_DIR		'/'
#define ENV_PWD		"PWD"
#define ENV_PATH	"PATH"

char	*ms_getpath_cmd(char *name);
char	*ms_getpath_relative(char *name);
char	*ms_getpath_envpath(char *name);
char	*ms_getpath_envpath_iter(char *name, char **envpath_split);
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

	envpath = ms_getenv_val(ENV_PATH);
	envpath_split = ft_split(envpath, ':');
	if (envpath_split == NULL)
		return (NULL);
	cmdpath = ms_getpath_envpath_iter(name, envpath_split);
	envpath_split = ms_mapclear(envpath_split, ms_mapsize(envpath_split));
	if (!cmdpath)
		cmdpath = ft_strdup("");
	return (cmdpath);
}

char	*ms_getpath_envpath_iter(char *name, char **envpath_split)
{
	char		*cmdpath;
	struct stat	stat_buf;
	size_t		i;

	if (envpath_split == NULL)
		return (NULL);
	i = 0;
	while (envpath_split[i])
	{
		cmdpath = ms_getpath_join(envpath_split[i], name);
		if (cmdpath == NULL)
			return (ms_mapclear(envpath_split, ms_mapsize(envpath_split)));
		stat(cmdpath, &stat_buf);
		if ((stat_buf.st_mode & S_IFMT) == S_IFREG)
			return (cmdpath);
		cmdpath = free_and_return(cmdpath);
		i++;
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

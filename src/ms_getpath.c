/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:11:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/06 19:54:14 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	cwd[PATH_MAX + 1];

	pwd = ms_getenv_val(ENV_PWD);
	if (pwd == NULL)
		path = ms_getpath_join(getcwd(cwd, PATH_MAX), name);
	else
		path = ms_getpath_join(pwd, name);
	return (path);
}

char	*ms_getpath_envpath(char *name)
{
	char		*cmdpath;
	char		*envpath;
	char		**envpath_split;

	envpath = ms_getenv_val(ENV_PATH);
	if (envpath == NULL)
		return (ft_strdup(name));
	envpath_split = ft_split(envpath, ':');
	if (envpath_split == NULL)
		return (NULL);
	cmdpath = ms_getpath_envpath_iter(name, envpath_split);
	envpath_split = ms_map_clear(envpath_split, ms_map_size(envpath_split));
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
			return (ms_map_clear(envpath_split, ms_map_size(envpath_split)));
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

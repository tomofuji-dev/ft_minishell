/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:17:50 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/01 17:16:25 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	pp_find_cmd(char *cmd_path, char *cmd_name, char **env_split)
{
	if (access(cmd_name, X_OK) == 0)
	{
		ft_strlcpy(cmd_path, cmd_name, 1024);
		return (true);
	}
	while (*env_split)
	{
		ft_strlcpy(cmd_path, *env_split, 1024);
		// todo: over 1024 case
		ft_strlcat(cmd_path, "/", 1024);
		ft_strlcat(cmd_path, cmd_name, 1024);
		if (access(cmd_path, X_OK) == 0)
			return (true);
		env_split++;
	}
	return (false);
}

//int	pp_exec(char *file1, char *cmd, char *envp[])
int	pp_exec(char *cmd, char **env_split, char **envp)
{
	char	**cmd_split;
	char	cmd_path[1024];
	int		errnum;

	cmd_split = ft_split(cmd, ' ');
	if (cmd_split == NULL)
		return (-1);
	if (pp_find_cmd(cmd_path, cmd_split[0], env_split) == false)
		return (-2);
	errnum = execve(cmd_path, cmd_split, envp);
	free(cmd_split);
	return (errnum);
}

char	**pp_split_path(char *envp[])
{
	char	*save;

	while (*envp != NULL)
	{
		save = *envp;
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(&(save[5]), ':'));
		envp++;
	}
	return (NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		errnum;
	char	**env_split;

	if (check_argc(argc) == false)
		return (1);
	env_split = pp_split_path(envp);
	if (env_split == NULL)
		return (2);
	errnum = pp_exec(argv[2], env_split, envp);
	free(env_split);
	return (errnum);
}

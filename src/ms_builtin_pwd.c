/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/19 14:44:46 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_pwd(char *argv[])
{
	char	buf[PATH_MAX];

	if (argv == NULL)
		return(0);
	errno = 0;
	printf("%s\n", getcwd(buf, PATH_MAX));
	return (errno);
}

/*
void	ms_builtin_pwd(t_cmd *cmd)
{
	char	**arg;

	if (cmd->arg[1] == NULL)
	{
		arg = (char **)malloc(3 * sizeof(char *));
		if (arg == NULL)
			return ;
		arg[1] = (char *)malloc((getenv(ENV_HOME) + ) * sizeof(char));
		if (arg == NULL)
			return ;
		arg[0] = cmd->arg[0];
		free (cmd->arg);
		cmd->arg = arg;
	}
}
*/

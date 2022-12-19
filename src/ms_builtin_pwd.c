/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/19 13:41:16 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

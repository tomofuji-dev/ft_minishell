/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/19 14:03:44 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*#include "minishell.h"

void	ms_builtin_cd(t_cmd *cmd)
{
	char	**arg;

	if (cmd == NULL)
		return ;
	if (cmd->arg[1] == NULL)
	{

	}
	else
	{
		chdir(cmd->arg[1]);
	}
}
*/
int	main()
{
	printf("HOME: %s\n", getenv("HOME"));
	chdir(getenv("HOME"));
	printf("PWD: %s\n", getenv("PWD"));
}

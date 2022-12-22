/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:14:42 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/22 14:21:24 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		g_shell;

void	init_global(char *envp[]);

void	init_global(char *envp[])
{
	size_t	env_count;

	env_count = ms_strlst_count(envp);
	g_shell.environ = malloc(sizeof(char *) * (env_count + 1));
	if (g_shell.environ == NULL)
		ms_strlst_cpy(g_shell.environ, envp);
	g_shell.status = 0;
}

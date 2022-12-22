/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:14:42 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/22 11:27:39 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		g_shell;

void	init_global(void);

void	init_global(void)
{
	size_t	env_count;

	env_count = ms_strlst_count(environ);
	g_shell.environ = malloc(sizeof(char *) * (env_count + 1));
	if (g_shell.environ == NULL)
		exit(EXIT_FAILURE);
	ms_strlst_cpy(g_shell.environ, environ);
	g_shell.status = 0;
}


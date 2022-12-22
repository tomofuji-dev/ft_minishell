/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:50:25 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/22 11:54:18 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv_line(char *env_key)
{
	size_t	i;

	i = 0;
	while (g_shell.environ[i] != NULL)
	{
		if (ft_strncmp(g_shell.environ[i], env_key, ft_strlen(env_key)) == 0)
			return (&g_shell.environ[i]);
		i++;
	}
	return (NULL);
}

char	*ms_getenv_val(char *env_key)
{
	char	*env_line;

	env_line = ms_getenv_line(env_key);
	if (env_line == NULL)
		return (NULL);
	return (ft_strchr(env_line, '=') + 1);
}

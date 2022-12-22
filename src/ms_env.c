/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:50:25 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/22 15:17:27 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv_line(char *env_key)
{
	t_list	*cur;

	cur = g_shell.environ;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->content, env_key, ft_strlen(env_key)) == 0)
			return (cur->content);
		cur = cur->next;
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

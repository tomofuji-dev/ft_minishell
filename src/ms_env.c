/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:50:25 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/23 17:30:42 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv_line(char *env_key);
char	*ms_getenv_val(char *env_key);
bool	ms_is_same_envkey(char *dest, char *src);
bool	ms_is_validenv(char *env_candidate);

char	*ms_getenv_line(char *env_key)
{
	t_list	*cur;

	cur = g_shell.environ;
	while (cur != NULL)
	{
		if (ms_is_same_envkey(cur->content, env_key))
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

bool	ms_is_same_envkey(char *dest, char *src)
{
	return (ft_strncmp(dest, src, ft_strlen(src)) == 0 \
			&& dest[ft_strlen(src)] == '=');
}

bool	ms_is_validenv(char *env_candidate)
{
	if (!(ft_isalpha(*env_candidate) || *env_candidate == '_'))
		return (false);
	env_candidate++;
	while (*env_candidate)
	{
		if (!ms_isenvchar(*env_candidate))
			return (false);
		env_candidate++;
	}
	return (true);
}

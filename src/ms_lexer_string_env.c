/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:05:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 15:37:23 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*ms_expand_envvar_dquote(char *line, size_t len);
t_list			*ms_expand_envvar(char *line, size_t *pos, size_t len);
bool			ms_isenvchar(int c);
static t_list	*ms_expand_special_env(char *line, size_t *pos);

t_list	*ms_expand_envvar_dquote(char *line, size_t len)
{
	size_t	pos;
	char	*dollar;
	t_list	*head;

	head = NULL;
	pos = 0;
	while (pos < len)
	{
		dollar = ft_strchr(&line[pos], '$');
		errno = 0;
		if (dollar == &line[pos])
			ft_lstadd_back(&head, ms_expand_envvar(line, &pos, len - pos));
		else
		{
			if (dollar == NULL || dollar >= line + len)
				dollar = line + len;
			ms_lstadd_back_substr(&head, line, pos, dollar - &line[pos]);
			pos = dollar - line;
		}
		if (errno == ENOMEM)
			exit(EXIT_FAILURE);
	}
	return (head);
}

t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len)
{
	size_t	i;
	char	*env_key;
	char	*env_val;

	*pos += 1;
	i = 0;
	if (line[*pos] == '?' || ft_isdigit(line[*pos]))
		return (ms_expand_special_env(line, pos));
	while (i + 1 < len && line[*pos + i] && ms_isenvchar(line[*pos + i]))
		i++;
	if (i == 0)
		return (ft_lstnew(ft_strdup("$")));
	env_key = ft_substr(line, *pos, i);
	*pos += i;
	if (env_key == NULL)
		exit(EXIT_FAILURE);
	env_val = ms_getenv_val(env_key);
	free(env_key);
	if (env_val == NULL)
		return (NULL);
	return (ft_lstnew(ft_strdup(env_val)));
}

bool	ms_isenvchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

static t_list	*ms_expand_special_env(char *line, size_t *pos)
{
	if (line[*pos] == '?')
	{
		*pos += 1;
		return (ft_lstnew(ft_itoa(g_shell.status)));
	}
	else if (ft_isdigit(line[*pos]))
	{
		*pos += 1;
		return (ft_lstnew(ft_strdup("")));
	}
	return (NULL);
}

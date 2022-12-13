/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:05:17 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 12:56:51 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_isenvchar(int c);
char	*ms_search_env(char *env_key);
t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len);
t_list	*ms_expand_envvar_dquote(char *line, size_t len);

bool	ms_isenvchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

// "$abc def" -> return "($abc_expanded)", and pos is set to " def"
// len is range to search
t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len)
{
	size_t	i;
	char	*env_key;
	char	*env_val;

	*pos += 1;
	i = 1;
	if (line[*pos] == '?')
	{
		*pos += 1;
		return (ft_lstnew(ft_strdup("?")));
	}
	while (i < len && line[*pos + i] && ms_isenvchar(line[*pos + i]))
		i++;
	if (i == 1)
		return (ft_lstnew("$"));
	env_key = ft_substr(line, *pos, i);
	*pos += i;
	if (errno == ENOMEM)
		exit(EXIT_FAILURE);
	env_val = ft_strdup(getenv(env_key));
	free(env_key);
	if (errno == ENOMEM)
		exit(EXIT_FAILURE);
	return (ft_lstnew(env_val));
}

// "abc $var def" -> "abc (expanded) def"
// line: not include dquote
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
			return (ms_lstclear_return_null(&head));
	}
	return (head);
}

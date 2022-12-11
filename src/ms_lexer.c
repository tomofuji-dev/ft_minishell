/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/11 13:54:27 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	init_global(void)
{
	extern char	**environ;

	g_shell.envp = environ;
}

size_t	ms_lexer_endpos_delim(char *line)
{
	int		ch;
	size_t	pos;

	if (!ft_strchr(&CHRS_DELIM[1], *line))
		return (0);
	ch = *line;
	pos = 0;
	while (*(line + pos) == ch)
		pos++;
	return (pos);
}

size_t	ms_lexer_endpos_quoted(char *line)
{
	int		ch;
	char	*line_end;

	if (!ft_strchr(CHRS_QUOTE, *line))
		return (0);
	ch = *line;
	line_end = ft_strchr(line + 1, ch);
	if (!line_end)
		return (1);
	return (line_end - line);
}

size_t	ms_lexer_endpos_plain(char *line)
{
	const char	*plain_delim = "\'\"$";
	size_t		i;

	i = 0;
	while (line[i] && !ft_strchr(plain_delim, line[i]))
		i++;
	return (i);
}

size_t	ms_lexer_endpos(char *line)
{
	size_t	pos;

	pos = 0;
	if (line == NULL)
		return (0);
	else if (ft_strchr(&CHRS_DELIM[1], *(line + pos)))
		return (ms_lexer_endpos_delim(line + pos));
	while (*(line + pos))
	{
		if (ft_strchr(CHRS_QUOTE, *(line + pos)))
			pos += ms_lexer_endpos_quoted(line + pos);
		else if (ft_strchr(CHRS_DELIM, *(line + pos)))
			return (pos);
		else
			pos++;
	}
	return (pos);
}

char	**ms_lexer_tokensize(char *line)
{
	size_t	size;
	size_t	pos;
	size_t	pos_end;

	if (line == NULL)
		return (0);
	size = 0;
	pos = 0;
	while (*line != '\0')
	{
		while (*line && *line == CHRS_DELIM[0])
			line++;
		if (ms_lexer_endpos(line))
			size++;
	}
	return (size);
}

void	*ms_lstclear_return_null(t_list **head)
{
	ft_lstclear(head, &free);
	return (NULL);
}

void	ms_lstadd_back_substr(t_list **head, char *line, size_t pos, size_t len)
{
	char	*substr;

	substr = ft_substr(line, pos, len);
	if (substr == NULL)
		return ;
	ft_lstadd_back(head, ft_lstnew(substr));
	return ;
}

bool	ms_isenvchar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ms_search_env(char *env_key)
{
	char	**cur;
	size_t	key_len;

	cur = g_shell.envp;
	key_len = ft_strlen(env_key);
	while (cur != NULL)
	{
		if (ft_strncmp(*cur, env_key, key_len) == 0)
			return (ft_substr(cur, key_len + 1, ft_strlen(&cur[key_len + 1])));
		cur++;
	}
	return (NULL);
}

// "$abc def" -> return "($abc_expanded)", and pos is set to " def"
// len is range to search
t_list	*ms_expand_envvar(char *line, size_t *pos, size_t len)
{
	size_t	i;
	char	*env_key;
	char	*env_val;

	if (line[*pos] != '$')
		return (NULL);
	*pos++;
	i = 1;
	while (i < len && line[*pos + i] && ms_isenvchar(line[*pos + i]))
		i++;
	if (i == 1)
		return (ft_lstnew("$"));
	else
	{
		env_key = ft_substr(line, *pos, i - 1);
		if (errno == ENOMEM)
			return (NULL);
		env_val = ms_search_env(env_key);
		free(env_key);
		if (env_val == NULL)
			return (NULL);
		else
			return (ft_lstnew(env_val));
	}
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
			if (dollar == NULL)
				dollar = line + len;
			ms_lstadd_back_substr(&head, line, pos, dollar - &line[pos]);
			pos = dollar - line;
		}
		if (errno == ENOMEM)
			return (ms_lstclear_return_null(&head));
	}
	return (head);
}

char	*ms_linkedls_to_str(t_list *head)
{
	size_t	joined_str_size;
	char	*joined_str;
	t_list	*cur;

	joined_str_size = 0;
	cur = head;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			joined_str_size += ft_strlen(cur->content);
		cur = cur->next;
	}
	joined_str = ft_calloc(joined_str_size, sizeof(char));
	if (errno == ENOMEM)
		return (NULL);
	cur = head;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			ft_strlcat(joined_str, cur->content, joined_str_size);
		cur = cur->next;
	}
	return (joined_str);
}

char	*ms_substr_and_expand(char *line)
{
	size_t		pos;
	size_t		stride;
	t_list		*head;
	char		*expand_str;

	pos = 0;
	head = NULL;
	while (line[pos])
	{
		if (line[pos] == '\'')
		{
			stride = ms_lexer_endpos_quoted(&line[pos]);
			if (stride > 2)
			{
				ms_lstadd_back_substr(&head, line, pos + 1, stride - 2);
				if (errno == ENOMEM)
					return (ms_lstclear_return_null(&head));
			}
			else if (stride == 1)
			{
				ft_lstadd_back(&head, ft_lstnew("\'"));
				if (errno == ENOMEM)
					return (ms_lstclear_return_null(&head));
			}
			pos += stride;
		}
		else if (line[pos] == '\"')
		{
			stride = ms_lexer_endpos_quoted(&line[pos]);
			if (stride > 2)
			{
				ft_lstadd_back(&head, \
						ms_expand_envvar_dquote(&line[pos + 1], stride - 2));
				if (errno == ENOMEM)
					return (ms_lstclear_return_null(&head));
			}
			else if (stride == 1)
			{
				ft_lstadd_back(head, ft_lstnew("\""));
				if (errno == ENOMEM)
					return (ms_lstclear_return_null(&head));
			}
			pos += stride;
		}
		else if (line[pos] == '$')
		{
			ft_lstadd_back(&head, \
				ms_expand_envvar(line, &pos, ft_strlen(&line[pos])));
			if (errno == ENOMEM)
				return (ms_lstclear_return_null(&head));
		}
		else
		{
			stride = ms_lexer_endpos_plain(&line[pos]);
			if (stride > 0)
			{
				ms_lstadd_back_substr(&head, line, pos, stride);
				if (errno == ENOMEM)
					return (ms_lstclear_return_null(&head));
			}
			pos += stride;
		}
	}
	expand_str = ms_linkedls_to_str(head);
	if (errno == ENOMEM)
		return (ms_lstclear_return_null(&head));
	ft_lstclear(&head, &free);
	return (expand_str);
}

t_token	*ms_lexer(char *line)
{
	t_token	*token;
	size_t	size;
	size_t	i;

	size = ms_lexer_tokensize(line);
	token = (t_token *)malloc((size + 1) * sizeof(t_token));
	i = 0;
	while (i < size)
	{
		token[i++] = ms_lexer_gettoken(line);
	}
	token[size + 1]->token == NULL;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:02:06 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 15:08:14 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ms_lexer_string(char *line);
static void	ms_lexer_string_quote(char *line, size_t *pos, t_list **head);
static void	ms_lexer_string_dquote(char *line, size_t *pos, t_list **head);
static void	ms_lexer_string_dollar(char *line, size_t *pos, t_list **head);
static void	ms_lexer_string_plain(char *line, size_t *pos, t_list **head);

char	*ms_lexer_string(char *line)
{
	size_t		pos;
	t_list		*head;
	char		*expand_str;

	pos = 0;
	head = NULL;
	while (line[pos])
	{
		if (line[pos] == '\'')
			ms_lexer_string_quote(line, &pos, &head);
		else if (line[pos] == '\"')
			ms_lexer_string_dquote(line, &pos, &head);
		else if (line[pos] == '$')
			ms_lexer_string_dollar(line, &pos, &head);
		else
			ms_lexer_string_plain(line, &pos, &head);
	}
	if (head == NULL)
		return (NULL);
	errno = 0;
	expand_str = ms_linkedls_to_str(head);
	if (errno == ENOMEM)
		return (ms_lstclear_return_null(&head));
	ft_lstclear(&head, &free);
	return (expand_str);
}

static void	ms_lexer_string_quote(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_quoted(&line[*pos]);
	errno = 0;
	if (stride > 2)
	{
		ms_lstadd_back_substr(head, line, *pos + 1, stride - 2);
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	else if (stride == 2)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup("")));
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	else if (stride == 1)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup("\'")));
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	*pos += stride;
}

static void	ms_lexer_string_dquote(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_quoted(&line[*pos]);
	errno = 0;
	if (stride > 2)
	{
		ft_lstadd_back(head, \
				ms_expand_envvar_dquote(&line[*pos + 1], stride - 2));
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	else if (stride == 2)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup("")));
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	else if (stride == 1)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup("\"")));
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	*pos += stride;
}

static void	ms_lexer_string_dollar(char *line, size_t *pos, t_list **head)
{
	errno = 0;
	ft_lstadd_back(head, \
		ms_expand_envvar(line, pos, ft_strlen(&line[*pos])));
	if (errno == ENOMEM)
		ms_lstclear_return_null(head);
}

static void	ms_lexer_string_plain(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_plain(&line[*pos]);
	if (stride > 0)
	{
		errno = 0;
		ms_lstadd_back_substr(head, line, *pos, stride);
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	*pos += stride;
}

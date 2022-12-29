/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:02:06 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/29 09:04:45 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_lexer_string(char *line);
void	ms_lexer_string_quote(char *line, size_t *pos, t_list **head);
void	ms_lexer_string_dquote(char *line, size_t *pos, t_list **head);
void	ms_lexer_string_dollar(char *line, size_t *pos, t_list **head);
void	ms_lexer_string_plain(char *line, size_t *pos, t_list **head);

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
	expand_str = ms_linkedls_to_str(head);
	if (errno == ENOMEM)
		return (ms_lstclear_return_null(&head));
	ft_lstclear(&head, &free);
	return (expand_str);
}

void	ms_lexer_string_quote(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_quoted(&line[*pos]);
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

void	ms_lexer_string_dquote(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_quoted(&line[*pos]);
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

void	ms_lexer_string_dollar(char *line, size_t *pos, t_list **head)
{
	ft_lstadd_back(head, \
		ms_expand_envvar(line, pos, ft_strlen(&line[*pos])));
	if (errno == ENOMEM)
		ms_lstclear_return_null(head);
}

void	ms_lexer_string_plain(char *line, size_t *pos, t_list **head)
{
	size_t	stride;

	stride = ms_lexer_tokenlen_plain(&line[*pos]);
	if (stride > 0)
	{
		ms_lstadd_back_substr(head, line, *pos, stride);
		if (errno == ENOMEM)
			ms_lstclear_return_null(head);
	}
	*pos += stride;
}

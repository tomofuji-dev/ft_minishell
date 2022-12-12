/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:02:06 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/12 10:37:04 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_lexer_string(char *line)
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
			stride = ms_lexer_tokenlen_quoted(&line[pos]);
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
			stride = ms_lexer_tokenlen_quoted(&line[pos]);
			if (stride > 2)
			{
				ft_lstadd_back(&head, \
						ms_expand_envvar_dquote(&line[pos + 1], stride - 2));
				if (errno == ENOMEM)
					return (ms_lstclear_return_null(&head));
			}
			else if (stride == 1)
			{
				ft_lstadd_back(&head, ft_lstnew("\""));
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
			stride = ms_lexer_tokenlen_plain(&line[pos]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:53:14 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/11 15:58:39 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ms_lexer(char *line);
size_t	ms_lexer_tokensize(char *line);

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

size_t	ms_lexer_tokensize(char *line)
{
	size_t	size;
	size_t	pos;
	size_t	len;

	if (line == NULL)
		return (0);
	size = 0;
	pos = 0;
	while (*(line + pos) != '\0')
	{
		while (*(line + pos) == CHRS_DELIM[0])
			pos++;
		len = ms_lexer_tokenlen(line + pos);
		if (len > 0)
			size++;
		pos += len;
	}
	return (size);
}

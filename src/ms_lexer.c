/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/07 16:33:18 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_lexer_endpos(char *line, size_t *size)
{
	size_t pos;

	pos = 0;
	while (*(line + pos))
	{
		if (*(line + pos) && !ft_strchr(CHRS_DELIM, *line))
			pos += ms_lexer_endpos_quoted(line + pos, size);
		else if (*(line + pos) && ft_strchr(&CHRS_DELIM[1], *line))
			pos += ms_lexer_pendos_delim(line + pos, size);
		else if (*(line + pos) == CHRS_DELIM[0])
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

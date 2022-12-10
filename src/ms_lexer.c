/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/10 14:30:47 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

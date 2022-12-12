/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_tokenlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:54:46 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 05:35:40 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_lexer_tokenlen(char *line);
size_t	ms_lexer_tokenlen_delim(char *line);
size_t	ms_lexer_tokenlen_quoted(char *line);
size_t	ms_lexer_tokenlen_plain(char *line);

size_t	ms_lexer_tokenlen(char *line)
{
	size_t	pos;

	pos = 0;
	if (line == NULL || *line == '\0')
		return (0);
	else if (ft_strchr(&CHRS_DELIM[1], *(line + pos)))
		return (ms_lexer_tokenlen_delim(line + pos));
	while (*(line + pos))
	{
		if (ft_strchr(CHRS_QUOTE, *(line + pos)))
			pos += ms_lexer_tokenlen_quoted(line + pos);
		else if (ft_strchr(CHRS_DELIM, *(line + pos)))
			return (pos);
		else
			pos++;
	}
	return (pos);
}

size_t	ms_lexer_tokenlen_delim(char *line)
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

size_t	ms_lexer_tokenlen_quoted(char *line)
{
	int		ch;
	char	*line_end;

	if (!ft_strchr(CHRS_QUOTE, *line))
		return (0);
	ch = *line;
	line_end = ft_strchr(line + 1, ch);
	if (!line_end)
		return (1);
	return (line_end - line + 1);
}

size_t	ms_lexer_tokenlen_plain(char *line)
{
	const char	*plain_delim = "\'\"$";
	size_t		i;

	i = 0;
	while (line[i] && !ft_strchr(plain_delim, line[i]))
		i++;
	return (i);
}

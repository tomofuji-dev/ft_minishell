/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_gettoken.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 13:01:56 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_token	*token;
	size_t	size;
	size_t	i;

	if (argc < 2)
		return (1);
	size = ms_lexer_tokensize(argv[1]);
	token = ms_lexer_gettoken(argv[1], size);
	printf("test {%s}\n", argv[1]);
	printf("token_size: %zu\n", size);
	i = 0;
	while (i < size)
	{
		printf("%2zd %#2x\t", i, token[i].flag);
		printf("{%s}\n", token[i].str);
		i++;
	}
	return (0);
}

// size_t	ms_lexer_tokenlen_delim(char *line)
// {
// 	int		ch;
// 	size_t	pos;

// 	if (!ft_strchr(&CHRS_DELIM[1], *line))
// 		return (0);
// 	ch = *line;
// 	pos = 0;
// 	while (*(line + pos) == ch)
// 		pos++;
// 	return (pos);
// }

// size_t	ms_lexer_tokenlen_quoted(char *line)
// {
// 	int		ch;
// 	char	*line_end;

// 	if (!ft_strchr(CHRS_QUOTE, *line))
// 		return (0);
// 	ch = *line;
// 	line_end = ft_strchr(line + 1, ch);
// 	if (!line_end)
// 		return (1);
// 	return (line_end - line + 1);
// }

// size_t	ms_lexer_tokenlen(char *line)
// {
// 	size_t	pos;

// 	pos = 0;
// 	if (line == NULL)
// 		return (0);
// 	else if (ft_strchr(&CHRS_DELIM[1], *(line + pos)))
// 		return (ms_lexer_tokenlen_delim(line + pos));
// 	while (*(line + pos))
// 	{
// 		if (ft_strchr(CHRS_QUOTE, *(line + pos)))
// 			pos += ms_lexer_tokenlen_quoted(line + pos);
// 		else if (ft_strchr(CHRS_DELIM, *(line + pos)))
// 			return (pos);
// 		else
// 			pos++;
// 	}
// 	return (pos);
// }

// size_t	ms_lexer_tokensize(char *line)
// {
// 	size_t	size;
// 	size_t	pos;
// 	size_t	len;

// 	if (line == NULL)
// 		return (0);
// 	size = 0;
// 	pos = 0;
// 	while (*(line + pos) != '\0')
// 	{
// 		while (*(line + pos) == CHRS_DELIM[0])
// 			pos++;
// 		len = ms_lexer_tokenlen(line + pos);
// 		if (len > 0)
// 			size++;
// 		pos += len;
// 	}
// 	return (size);
// }

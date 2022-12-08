/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/08 17:09:58 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	test_print_argv(int argc, char *argv[])
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf("argv[%d]: {%s}\n", i, argv[i]);
		i++;
	}
	return ;
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
		else if (ft_strchr(&CHRS_DELIM[1], *(line + pos)))
			return (pos);
		else
			pos++;
	}
	return (pos);
}

void	test_ms_lexer_endpos(void)
{
	char	str[] = "a>bc<def>>ghij<<klm>>>n<<<<op><q|rs||tu|<vw|>x\'y\"z|><12\'34\"56\'78\"9ab\"cdefghi";
	char	*cur;
	size_t	s;

	cur = str;
	while (*cur != '\0')
	{
		s = ms_lexer_endpos(cur);
		write(1, cur, s);
		write(1, "\n", 1);
		cur = cur + s;
	}
	return ;
}

int	main(void)
{
	test_ms_lexer_endpos();
	return (0);
}

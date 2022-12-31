/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/29 00:58:52 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void	test_ms_lexer_endpos(void)
{
	const char	str[] = "a b  c>bc<def>>ghij<<klm>>>n<<<<o\
	p><q|rs||tu|<vw|>x\'y\"z|><12\'34\"56\'78\"9ab\"cdefghi";
	char		*cur;
	size_t		s;

	cur = str;
	while (*cur != '\0')
	{
		s = ms_lexer_endpos(cur);
		write(1, cur, s);
		write(1, "\n", 1);
		cur = cur + s;
		while (*cur && *cur == CHRS_DELIM[0])
			cur++;
	}
	return ;
}

int	main(void)
{
	test_ms_lexer_endpos();
	return (0);
}

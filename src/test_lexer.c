/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 13:14:22 by tfujiwar         ###   ########.fr       */
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

void	test_ms_lexer_endpos(void)
{
	char	str[] = "a b  c>bc<def>>ghij<<klm>>>n<<<<op><q|rs||tu|<vw|>x\'y\"z|><12\'34\"56\'78\"9ab\"cdefghi";
	char	*cur;
	size_t	s;

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

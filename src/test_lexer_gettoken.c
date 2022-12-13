/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer_gettoken.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/13 13:14:02 by tfujiwar         ###   ########.fr       */
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

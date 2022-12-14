/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 17:40:05 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_token	*token;
	t_cmd	*cmd;
	size_t	i;

	if (argc < 2)
		return (1);
	token = ms_lexer(argv[1]);
	cmd = ms_parser(token);
	printf("test {%s}\n", argv[1]);
	printf("token_size: %zu\n", size);
	while (cmd != NULL)
	{
		printf("%2zd %#2x\t", i, token[i].flag);
		printf("{%s}\n", token[i].str);
		cmd == cmd->next;
	}
	return (0);
}

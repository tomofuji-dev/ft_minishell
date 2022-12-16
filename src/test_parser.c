/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:47:24 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/16 15:08:21 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_token	*token;
	t_cmd	*cmd;

	if (argc < 2)
		return (1);
	printf("test {%s}\n", argv[1]);
	token = ms_lexer(argv[1]);
	cmd = ms_parser(token);
	while (cmd != NULL)
	{
		printf("path: %s\n", cmd->path);
		while (*(cmd->arg) != NULL)
		{
			printf("arg: %s\n", *(cmd->arg));
			(cmd->arg)++;
		}
		printf("input: ");
		while (cmd->input->path != NULL)
		{
			printf("%d -> ", cmd->input->fd);
			(cmd->input)++;
		}
		printf("\noutput: ");
		while (cmd->output->path != NULL)
		{
			printf("%d -> ", cmd->output->fd);
			(cmd->output)++;
		}
		printf("\n");
		cmd = cmd->next;
	}
	return (0);
}

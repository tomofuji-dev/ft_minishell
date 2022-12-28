/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/29 00:49:47 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_parser_cmdnew(t_token *token, size_t *idx)
{
	t_cmd	*cmd;

	if (token == NULL || token[*idx].str == NULL)
		return (NULL);
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->arg = ms_parser_cmdnew_arg(token, *idx);
	if (cmd->arg == NULL)
		return (ms_clear_cmd_and_return_null(cmd));
	cmd->path = ms_getpath_cmd(cmd->arg[0]);
	if (cmd->path == NULL)
		return (ms_clear_cmd_and_return_null(cmd));
	cmd->input = ms_parser_cmdnew_input(token, *idx);
	if (cmd->input == NULL)
		return (ms_clear_cmd_and_return_null(cmd));
	cmd->output = ms_parser_cmdnew_output(token, *idx);
	if (cmd->output == NULL)
		return (ms_clear_cmd_and_return_null(cmd));
	while (token[*idx].str != NULL && token[*idx].flag != FLAG_PIPE)
		(*idx)++;
	return (cmd);
}

//	printf("parser_cmdnew/cmd->arg: %s\n", cmd->arg[0]);
//	printf("parser_cmdnew/cmd->input: %s\n", cmd->input[0].path);
//	printf("parser_cmdnew/cmd->output: %s\n", cmd->output[0].path);

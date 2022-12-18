/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/18 15:16:08 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_parser_cmdnew(t_token *token, size_t *idx)
{
	t_cmd	*cmd;

	if (token == NULL || token[*idx].str == NULL)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->arg = ms_parser_cmdnew_arg(token, *idx);
//	printf("parser_cmdnew/cmd->arg: %s\n", cmd->arg[0]);
	if (cmd->arg == NULL)
		return (free_and_return(cmd));
	cmd->path = ms_getpath_cmd(cmd->arg[0]);
	if (cmd->path == NULL)
		return (free_and_return(cmd));
	cmd->input = ms_parser_cmdnew_input(token, *idx);
//	printf("parser_cmdnew/cmd->input: %s\n", cmd->input[0].path);
	if (cmd->input == NULL)
		return (free_and_return(cmd));
	cmd->output = ms_parser_cmdnew_output(token, *idx);
//	printf("parser_cmdnew/cmd->output: %s\n", cmd->output[0].path);
	if (cmd->output == NULL)
		return (free_and_return(cmd));
	while (token[*idx].str != NULL && token[*idx].flag != FLAG_PIPE)
		(*idx)++;
	return (cmd);
}

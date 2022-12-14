/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 16:13:39 by tfujiwar         ###   ########.fr       */
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
	if (cmd->arg == NULL)
		return (free_and_return(cmd));
	cmd->path = ms_parser_cmdnew_path(cmd->arg[0]);
	if (cmd->path == NULL)
		return (free_and_return(cmd));
	cmd->input = ms_parser_cmdnew_input(token, *idx);
	if (cmd->input == NULL)
		return (free_and_return(cmd));
	cmd->output = ms_parser_cmdnew_output(token, *idx);
	if (cmd->output == NULL)
		return (free_and_return(cmd));
	while (token[*idx].str != NULL && token[*idx].flag != FLAG_PIPE)
		*idx++;
	return (cmd);
}

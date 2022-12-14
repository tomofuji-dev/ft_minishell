/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 14:45:18 by tfujiwar         ###   ########.fr       */
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
	cmd->input = ms_parser_cmdnew_input(token, *idx);
	cmd->output = ms_parser_cmdnew_output(token, *idx);
	while (token[*idx].str != NULL && token[*idx].flag != FLAG_PIPE)
		*idx++;
	return (cmd);
}

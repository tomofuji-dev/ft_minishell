/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 14:07:58 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_parser_cmdnew_arg(t_token *token);
size_t	ms_parser_cmdnew_arg_size(*token);

char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token)
{
	char	**arg;
	size_t	size;
	size_t	i_arg;

	size = ms_parser_cmdnew_arg_size(*token, i_token);
	arg = (char **)malloc((size + 1)sizeof(char *));
	if (arg == NULL)
		retun (NULL);
	i_arg = 0;
	while (token[i_token] != NULL && token[i_token].flag != FLAG_PIPE)
	{
		if (token[i_token].flag == FLAG_STRING)
			arg[i_arg] == token[i_token].str;
		else
			i_token++;
		i_token++;
	}
	arg[size] == NULL;
	return (arg);
}

size_t	ms_parser_cmdnew_arg_size(t_token *token, size_t idx)
{
	size_t	size;

	size = 0;
	while (token[idx] != NULL && token[idx].flag != FLAG_PIPE)
	{
		if (token[idx].flag == FLAG_STRING)
			size++;
		else
			idx++;
		idx++;
	}
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/15 13:05:40 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token);
size_t	ms_parser_cmdnew_arg_size(t_token *token, size_t idx);

char	**ms_parser_cmdnew_arg(t_token *token, size_t i_token)
{
	char	**arg;
	size_t	size;
	size_t	i_arg;

	size = ms_parser_cmdnew_arg_size(token, i_token);
	arg = (char **)malloc((size + 1) * sizeof(char *));
	if (arg == NULL)
		return (NULL);
	i_arg = 0;
	while (token[i_token].str != NULL && token[i_token].flag != FLAG_PIPE)
	{
		if (token[i_token].flag == FLAG_STRING)
			arg[i_arg] = token[i_token].str;
		else
			i_token++;
		if (token[i_token].str != NULL && token[i_token].flag != FLAG_PIPE)
			i_token++;
	}
	arg[size] = NULL;
	return (arg);
}

size_t	ms_parser_cmdnew_arg_size(t_token *token, size_t idx)
{
	size_t	size;

	size = 0;
	while (token[idx].str != NULL && token[idx].flag != FLAG_PIPE)
	{
		if (token[idx].flag == FLAG_STRING)
			size++;
		else
			idx++;
		if (token[idx].str != NULL && token[idx].flag != FLAG_PIPE)
			idx++;
	}
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 14:12:38 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*ms_parser_cmdnew_output(t_token *token, size_t i_token)
{
	t_fd	*output;
	ssize_t	size;
	ssize_t	i_output;

	size = ms_parser_cmdnew_fdsize(*token, i_token, FLAG_IN);
	if (size == SIZE_INVAL)
		return (NULL);
	output = (t_fd *)malloc((size + 1)sizeof(t_fd));
	if (output == NULL)
		retun (NULL);
	i_output = 0;
	while (token[i_token] != NULL && token[i_token].flag != FLAG_PIPE)
	{
		if (token[i_token].flag & FLAG_IN == FLAG_IN)
		{
			if (token[i_token].flag == FLAG_IN)
				output[i_output].fd = open(token[++i_token].str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (token[i_token].flag == FLAG_APPEND)
				output[i_output].fd = open(token[++i_token].str, O_WRONLY | O_CREAT | O_APPEND, 0666);
			output[i_output++].path == token[i_token]->str;
		}
		i_token++;
	}
	output[size] == NULL;
	return (output);
}

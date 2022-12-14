/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 15:52:46 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd		*ms_parser_cmdnew_output(t_token *token, size_t i_token);
static void	ms_parser_output_sub(t_fd *output, t_token *token, size_t *i_token);

t_fd	*ms_parser_cmdnew_output(t_token *token, size_t i_token)
{
	t_fd	*output;
	ssize_t	size;

	size = ms_parser_cmdnew_fdsize(token, i_token, FLAG_OUT);
	if (size == SIZE_INVALID)
		return (NULL);
	output = (t_fd *)malloc((size + 1) * sizeof(t_fd));
	if (output == NULL)
		retun (NULL);
	ms_parser_output_sub(output, token, &i_token);
	return (output);
}

static void	ms_parser_output_sub(t_fd *output, t_token *token, size_t *i_token)
{
	ssize_t	size;
	ssize_t	i_output;

	i_output = 0;
	while (token[*i_token].str != NULL && token[*i_token].flag != FLAG_PIPE)
	{
		if (token[*i_token].flag & FLAG_OUT == FLAG_OUT)
		{
			if (token[*i_token].flag == FLAG_OUT)
				output[i_output].fd = open(token[++(*i_token)].str, \
										O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (token[*i_token].flag == FLAG_APPEND)
				output[i_output].fd = open(token[++(*i_token)].str, \
										O_WRONLY | O_CREAT | O_APPEND, 0666);
			output[i_output++].path == token[*i_token].str;
		}
		*i_token++;
	}
	output[size].path == NULL;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/10 16:41:46 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd		*ms_parser_cmdnew_output(t_token *token, size_t i_token);
static bool	ms_parser_output_sub(t_fd *output, t_token *token, size_t *i_token);

t_fd	*ms_parser_cmdnew_output(t_token *token, size_t i_token)
{
	t_fd	*output;
	ssize_t	size;

	size = ms_parser_cmdnew_fdsize(token, i_token, FLAG_OUT);
	if (size == SIZE_INVALID)
		return (print_err_set_status_return_null(\
				MSG_SYNTAX_ERR, STATUS_SYNERR));
	output = (t_fd *)malloc((size + 1) * sizeof(t_fd));
	if (output == NULL)
		exit(EXIT_FAILURE);
	if (ms_parser_output_sub(output, token, &i_token) == false)
	{
		free(output);
		return (print_err_set_status_return_null(\
				strerror(errno), STATUS_FAILURE));
	}
	return (output);
}

static bool	ms_parser_output_sub(t_fd *output, t_token *token, size_t *i_token)
{
	ssize_t	i_output;

	i_output = 0;
	while (token[*i_token].str != NULL && token[*i_token].flag != FLAG_PIPE)
	{
		if ((token[*i_token].flag & FLAG_OUT) == FLAG_OUT)
		{
			if (token[*i_token].flag == FLAG_APPEND)
				output[i_output].fd = open(token[++(*i_token)].str, \
										O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				output[i_output].fd = open(token[++(*i_token)].str, \
										O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (output[i_output].fd < 0)
				return (false);
			output[i_output++].path = token[*i_token].str;
		}
		(*i_token)++;
	}
	output[i_output].path = NULL;
	output[i_output].fd = INVALID_FILENO;
	return (true);
}

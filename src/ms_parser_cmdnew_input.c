/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 14:12:15 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*ms_parser_cmdnew_input(t_token *token, size_t i_token)
{
	t_fd	*input;
	ssize_t	size;
	ssize_t	i_input;

	size = ms_parser_cmdnew_fdsize(*token, i_token, FLAG_IN);
	if (size == SIZE_INVAL)
		return (NULL);
	input = (t_fd *)malloc((size + 1)sizeof(t_fd));
	if (input == NULL)
		retun (NULL);
	i_input = 0;
	while (token[i_token] != NULL && token[i_token].flag != FLAG_PIPE)
	{
		if (token[i_token].flag & FLAG_IN == FLAG_IN)
		{
			if (token[i_token].flag == FLAG_IN)
				input[i_input].fd = open(token[++i_token].str, O_RDONLY);
			else if (token[i_token].flag == FLAG_HEREDOC)
				input[i_input].fd = get_heredoc_pipe(token[++i_token].str);
			input[i_input++].path == token[i_token]->str;
		}
		i_token++;
	}
	input[size] == NULL;
	return (input);
}

static int	get_heredoc_pipe(const char *eof)
{
	int	fd[2];

	pipe(fd);
	get_heredoc_txt(eof, fd[0]);
	close(fd[0]);
	return (fd[1]);
}

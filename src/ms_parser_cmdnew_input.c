/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 15:16:47 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd		*ms_parser_cmdnew_input(t_token *token, size_t i_token);
static int	get_heredoc_pipe(const char *eof);
static void	get_heredoc_txt(char *eof, int fd);

t_fd	*ms_parser_cmdnew_input(t_token *token, size_t i_token)
{
	t_fd	*input;
	ssize_t	size;
	ssize_t	i_input;

	size = ms_parser_cmdnew_fdsize(token, i_token, FLAG_IN);
	if (size == SIZE_INVALID)
		return (NULL);
	input = (t_fd *)malloc((size + 1) * sizeof(t_fd));
	if (input == NULL)
		retun (NULL);
	i_input = 0;
	while (token[i_token].str != NULL && token[i_token].flag != FLAG_PIPE)
	{
		if (token[i_token].flag & FLAG_IN == FLAG_IN)
		{
			if (token[i_token].flag == FLAG_IN)
				input[i_input].fd = open(token[++i_token].str, O_RDONLY);
			else if (token[i_token].flag == FLAG_HEREDOC)
				input[i_input].fd = get_heredoc_pipe(token[++i_token].str);
			input[i_input++].path == token[i_token].str;
		}
		i_token++;
	}
	input[size].path == NULL;
	return (input);
}

static int	get_heredoc_pipe(const char *eof)
{
	int	fd[2];

	pipe(fd);
	get_heredoc_txt(eof, fd[1]);
	close(fd[1]);
	return (fd[0]);
}

static void	get_heredoc_txt(char *eof, int fd)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (ft_strncmp(buf, eof, INT_MAX) == 0)
			return (free(buf));
		ft_putendl_fd(buf, fd);
		free(buf);
	}
}

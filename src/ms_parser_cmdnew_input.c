/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/10 16:39:47 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd		*ms_parser_cmdnew_input(t_token *token, size_t i_token);
static bool	ms_parser_input_sub(t_fd *input, t_token *token, size_t *i_token);
static int	get_heredoc_pipe(const char *eof);
static int	is_heredoc_sigint(void);
static bool	get_heredoc_txt(const char *eof, int fd);

t_fd	*ms_parser_cmdnew_input(t_token *token, size_t i_token)
{
	t_fd	*input;
	ssize_t	size;

	size = ms_parser_cmdnew_fdsize(token, i_token, FLAG_IN);
	if (size == SIZE_INVALID)
		return (print_err_set_status_return_null(\
				MSG_SYNTAX_ERR, STATUS_SYNERR));
	input = (t_fd *)malloc((size + 1) * sizeof(t_fd));
	if (input == NULL)
		exit(EXIT_FAILURE);
	errno = 0;
	if (ms_parser_input_sub(input, token, &i_token) == false)
	{
		free(input);
		if (errno == 0)
		{
			if (g_shell.heredoc_sigint == false)
				g_shell.status = 0;
			return (NULL);
		}
		return (print_err_set_status_return_null(\
				strerror(errno), STATUS_FAILURE));
	}
	return (input);
}

static bool	ms_parser_input_sub(t_fd *input, t_token *token, size_t *i_token)
{
	ssize_t	i_input;

	i_input = 0;
	while (token[*i_token].str != NULL && token[*i_token].flag != FLAG_PIPE)
	{
		if ((token[*i_token].flag & FLAG_IN) == FLAG_IN)
		{
			if (token[*i_token].flag == FLAG_HEREDOC)
				input[i_input].fd = get_heredoc_pipe(token[++(*i_token)].str);
			else
				input[i_input].fd = open(token[++(*i_token)].str, O_RDONLY);
			if (input[i_input].fd < 0)
				return (false);
			input[i_input++].path = token[*i_token].str;
		}
		(*i_token)++;
	}
	input[i_input].path = NULL;
	input[i_input].fd = INVALID_FILENO;
	return (true);
}

static int	get_heredoc_pipe(const char *eof)
{
	int	fd[2];

	pipe(fd);
	if (get_heredoc_txt(eof, fd[1]))
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		ms_fd_close(fd);
		return (INVALID_FILENO);
	}
}

static int	is_heredoc_sigint(void)
{
	if (g_shell.heredoc_sigint)
		rl_done = 1;
	return (STATUS_SUCCESS);
}

static bool	get_heredoc_txt(const char *eof, int fd)
{
	char	*buf;

	ms_sigset_rl_heredoc();
	rl_event_hook = is_heredoc_sigint;
	while (g_shell.heredoc_sigint == false)
	{
		buf = readline(PROMPT_HREDOC);
		if (!buf)
			return (true);
		if (ft_strncmp(buf, eof, INT_MAX) == 0)
		{
			free(buf);
			return (true);
		}
		ft_putendl_fd(buf, fd);
		free(buf);
	}
	return (false);
}

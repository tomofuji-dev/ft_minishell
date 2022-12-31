/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 16:42:59 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char *argv[], char *envp[]);
static char	*ms_readline(void);
static void	ms_clear_token(t_token *token);

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_token	*token;

	(void)argc;
	(void)argv;
	init_global(envp);
	while (1)
	{
		line = ms_readline();
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			token = ms_lexer(line);
			g_shell.cmd = ms_parser(token);
			ms_sigset_exec();
			ms_exec(g_shell.cmd);
			ms_clear_token(token);
		}
		free(line);
	}
	ms_builtin_exit(NULL);
	return (g_shell.status);
}

static char	*ms_readline(void)
{
	char	*line;

	ms_sigset_rl();
	ms_sigset_noquit();
	rl_done = 0;
	rl_event_hook = NULL;
	line = readline(PROMPT_MINISH);
	if (line == NULL)
		return (NULL);
	return (line);
}

static void	ms_clear_token(t_token *token)
{
	size_t	i;

	if (token == NULL)
		return ;
	i = 0;
	while (&token[i] && token[i].str)
	{
		free(token[i].str);
		i++;
	}
	free(token);
}

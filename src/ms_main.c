/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 12:04:30 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[], char *envp[]);
void	ms_exec(t_cmd *cmd);
int		ms_cmdsize(t_cmd *cmd);
char	*ms_readline(void);
void	ms_clear_token(t_token *token);

void	ms_exec(t_cmd *cmd)
{
	int	(*builtin)(char *arg[]);

	if (cmd == NULL)
		return ;
	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL && ms_cmdsize(cmd) == 1)
		ms_exec_a_builtin(cmd, builtin);
	else
		ms_exec_in_child_process(cmd);
	ms_clear_cmd_and_return_null(cmd);
}

int	ms_cmdsize(t_cmd *cmd)
{
	int	size;

	size = 0;
	while (cmd != NULL)
	{
		size++;
		cmd = cmd->next;
	}
	return (size);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_token	*token;

	(void)argc;
	(void)argv;
	init_global(envp);
	while (1)
	{
		ms_sigset_rl();
		ms_sigset_noquit();
		line = ms_readline();
		if (line == NULL)
			break ;
		if (*line)
		{
			token = ms_lexer(line);
			g_shell.cmd = ms_parser(token);
			ms_sigset_exec();
			ms_exec(g_shell.cmd);
			ms_clear_token(token);
			free(line);
		}
	}
	ms_builtin_exit(NULL);
	return (g_shell.status);
}

char	*ms_readline(void)
{
	char	*line;

	rl_done = 0;
	rl_event_hook = NULL;
	line = readline("minishell $ ");
	if (line == NULL)
		return (NULL);
	add_history(line);
//	rl_replace_line("", 0);
//	rl_on_new_line();
//	rl_redisplay();
//	rl_clear_history();
	return (line);
}

void	ms_clear_token(t_token *token)
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

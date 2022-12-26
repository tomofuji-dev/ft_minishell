/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/27 00:54:11 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[], char *envp[]);
void	ms_exec(t_cmd *cmd);
int		ms_cmdsize(t_cmd *cmd);
char	*ms_readline(void);

void	ms_exec(t_cmd *cmd)
{
	int	(*builtin)(char *arg[]);

	builtin = ms_builtin_getfunc(cmd->arg[0]);
	if (builtin != NULL && ms_cmdsize(cmd) == 1)
		return (ms_exec_a_builtin(cmd, builtin));
	else
		return (ms_exec_in_child_process(cmd));
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
	t_cmd	*cmd;

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
			token = ms_lexer(line);
			cmd = ms_parser(token);
			if (cmd != NULL)
				ms_exec(cmd);
		}
	}
	return (g_shell.status);
}

char	*ms_readline(void)
{
	char	*line;

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

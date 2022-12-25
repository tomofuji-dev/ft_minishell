/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/25 14:36:37 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[], char *envp[]);
void	ms_exec(t_cmd *cmd);
int		ms_cmdsize(t_cmd *cmd);

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
		line = readline("minishell $ ");
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

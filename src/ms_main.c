/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/22 14:22:50 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void);
void	exec(t_cmd *cmd);
int		ms_cmdsize(t_cmd *cmd);

void	exec(t_cmd *cmd)
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

int	main(int argc, char *argv, char *envp[])
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;

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
			exec(cmd);
		}
	}
	return (g_shell->status);
}

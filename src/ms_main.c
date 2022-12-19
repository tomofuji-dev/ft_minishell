/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/18 17:03:38 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char		**environ;
int				status;

void	(*ms_get_builtin(t_cmd *cmd))(t_cmd *s)
{
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		return (ms_builtin_echo);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (ms_builtin_cd);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		return (ms_builtin_pwd);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		return (ms_builtin_export);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		return (ms_builtin_unset);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		return (ms_builtin_env);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (ms_builtin_exit);
	return (NULL);
}

void	exec(t_cmd *cmd)
{
	(void *) buitin;

	builtin = ms_isbuiltin(cmd->arg[0]);
	if (builtin != NULL && ms_cmd_size(cmd) == 1)
		return (ms_exec_a_builtin(cmd, f));
	else
		return (ms_exec_in_child_process(cmd)); // 最初がbuiltinだったらforkせずに関数を実行してからforkを始める
}

int	main(void)
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;

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
	return (status);
}

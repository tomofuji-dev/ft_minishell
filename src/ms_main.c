/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:08:21 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/18 14:48:12 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char		**environ;
int				status;

void	exec(t_cmd *cmd)
{
	if (cmd_size(cmd) == 1 && ms_isbuitin(line))
		return (exec_a_builtin(cmd));
	else
		return (exec_in_child_process(cmd));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2022/12/31 16:42:59 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sighandler_rl(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT)
		ms_builtin_exit(NULL);
	if (signum == SIGINT)
	{
		g_shell.status = STATUS_BASE + signum;
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ms_sighandler_rl_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		g_shell.status = STATUS_BASE + signum;
		g_shell.heredoc_sigint = true;
	}
}

void	ms_sighandler_exec(int signum, siginfo_t *info, void *context)
{
	t_cmd	*cur;

	(void)context;
	(void)info;
	if (signum == SIGQUIT || signum == SIGINT)
	{
		g_shell.status = STATUS_BASE + signum;
		g_shell.kill_child = true;
		cur = g_shell.cmd;
		while (cur != NULL)
		{
			kill(cur->pid, signum);
			cur = cur->next;
		}
		if (signum == SIGQUIT)
			ft_putendl_fd(MSG_SIG_QUIT, STDOUT_FILENO);
		if (signum == SIGINT)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

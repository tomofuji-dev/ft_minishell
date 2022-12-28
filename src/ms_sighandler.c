/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2022/12/28 13:47:41 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static volatile sig_atomic_t	g_signum = SIG_NONE;

void	ms_sighandler_rl(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT)
		ms_builtin_exit(NULL);
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
//	write(2, ft_itoa(info->si_pid), 6);
//	write(2, STR_INFO, ft_strlen(STR_INFO));
//	g_signum = signum;
}

void	ms_sighandler_rl_heredoc(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
//	write(2, ft_itoa(info->si_pid), 6);
//	write(2, STR_INFO, ft_strlen(STR_INFO));
//	g_signum = signum;
}

void	ms_sighandler_exec(int signum, siginfo_t *info, void *context)
{
	t_cmd	*cur;

	(void)context;
	(void)info;
	if (signum == SIGQUIT || signum == SIGINT)
	{
		cur = g_shell.cmd;
		while (cur != NULL)
		{
			kill(cur->pid, signum);
			cur = cur->next;
		}
		if (signum == SIGQUIT)
			ft_putendl_fd("Quit: 3", 1);
	}
//	write(2, ft_itoa(info->si_pid), 6);
//	write(2, STR_INFO, ft_strlen(STR_INFO));
//	g_signum = signum;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2022/12/27 16:39:44 by Yoshihiro K      ###   ########.fr       */
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
		rl_replace_line("replace\n", 0);
//		rl_on_new_line();
//		rl_redisplay();
	}
//	write(2, ft_itoa(info->si_pid), 6);
//	write(2, STR_INFO, ft_strlen(STR_INFO));
//	g_signum = signum;
}

void	ms_sighandler_exec(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGTERM || signum == SIGQUIT)
		ms_builtin_exit(NULL);
//	write(2, ft_itoa(info->si_pid), 6);
//	write(2, STR_INFO, ft_strlen(STR_INFO));
//	g_signum = signum;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sigset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:04:04 by ykosaka           #+#    #+#             */
/*   Updated: 2022/12/30 14:43:31 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_sigset_rl(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ms_sighandler_rl;
	sigaction(SIGINT, &sa, NULL);
//	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(SIGTERM, &sa, NULL);
}

void	ms_sigset_noquit(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ms_sigset_rl_heredoc(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ms_sighandler_rl_heredoc;
	sigaction(SIGINT, &sa, NULL);
}

void	ms_sigset_exec(void)
{
	t_sa	sa;

	ft_bzero(&sa, sizeof(t_sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ms_sighandler_exec;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(SIGTERM, &sa, NULL);
}

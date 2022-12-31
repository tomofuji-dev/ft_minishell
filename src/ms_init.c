/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:14:42 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 15:51:16 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		g_shell;

void			init_global(char *envp[]);
static t_list	*ms_tlst_from_strlst(char *envp[]);

void	init_global(char *envp[])
{
	g_shell.environ = ms_tlst_from_strlst(envp);
	g_shell.status = 0;
	g_shell.cmd = NULL;
	g_shell.kill_child = false;
	g_shell.heredoc_sigint = false;
}

static t_list	*ms_tlst_from_strlst(char *envp[])
{
	t_list	head;
	t_list	*cur;
	char	*content;
	size_t	i;

	head.next = NULL;
	cur = &head;
	i = 0;
	while (envp[i] != NULL)
	{
		content = ft_strdup(envp[i]);
		if (content == NULL)
			exit(EXIT_FAILURE);
		cur->next = ft_lstnew(content);
		if (cur->next == NULL)
			exit(EXIT_FAILURE);
		cur = cur->next;
		i++;
	}
	return (head.next);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:14:42 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/22 15:07:24 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		g_shell;

void	init_global(char *envp[]);
t_list	*ms_tlst_from_strlst(char *envp[]);

void	init_global(char *envp[])
{
	size_t	env_count;

	g_shell.environ = ms_tlst_from_strlst(envp);
	g_shell.status = 0;
}

t_list	*ms_tlst_from_strlst(char *envp[])
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
	}
	return (head->next);
}

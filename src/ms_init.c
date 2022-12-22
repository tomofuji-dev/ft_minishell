/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:14:42 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/23 06:07:48 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		g_shell;

void	init_global(char *envp[]);
t_list	*ms_tlst_from_strlst(char *envp[]);

void	init_global(char *envp[])
{
<<<<<<< HEAD

	g_shell.environ->content = ms_tlst_from_strlst(envp);
=======
	g_shell.environ = ms_tlst_from_strlst(envp);
>>>>>>> 53221feb0165b917fc63b0e7b437ac0eef7fb2bd
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
		i++;
	}
	return (head.next);
}

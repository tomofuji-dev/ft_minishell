/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:42:18 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/31 15:25:13 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ms_builtin_unset(char *argv[]);
static void	ms_search_env_and_unset(char *env_key);

int	ms_builtin_unset(char *argv[])
{
	int	return_status;
	int	i;

	return_status = STATUS_SUCCESS;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ms_is_validenv(argv[i]) == false)
		{
			printf(MSG_INVAL_ID, CMD_UNSET, argv[i++]);
			return_status = STATUS_FAILURE;
			continue ;
		}
		ms_search_env_and_unset(argv[i]);
		i++;
	}
	return (return_status);
}

static void	ms_search_env_and_unset(char *env_key)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*tmp;

	cur = g_shell.environ;
	prev = NULL;
	while (cur != NULL)
	{
		if (ms_is_same_envkey(cur->content, env_key))
		{
			if (prev == NULL)
				g_shell.environ = cur->next;
			else
				prev->next = cur->next;
			tmp = cur->next;
			ft_lstdelone(cur, &free);
			cur = tmp;
			return ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

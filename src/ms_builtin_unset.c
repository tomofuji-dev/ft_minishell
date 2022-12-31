/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:42:18 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/23 06:21:46 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:39:51 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/23 10:41:46 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_builtin_unset(char *argv[]);
void	ms_search_env_and_unset(char *env_key);

int	ms_builtin_unset(char *argv[])
{
	int	return_status;
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		ms_search_env_and_unset(argv[i]);
		i++;
	}
	return_status = 0;
	return (return_status);
}

void	ms_search_env_and_unset(char *env_key)
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


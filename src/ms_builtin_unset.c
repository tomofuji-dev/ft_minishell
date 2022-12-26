/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:42:18 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/26 11:23:41 by tfujiwar         ###   ########.fr       */
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

	return_status = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ms_is_validenv(argv[i]) == false)
		{
			printf("bash: unset: `%s\" : not a valid identifier\n", argv[i++]);
			return_status = 1;
			continue ;
		}
		ms_search_env_and_unset(argv[i]);
		i++;
	}
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


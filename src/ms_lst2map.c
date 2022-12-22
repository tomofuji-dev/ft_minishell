/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst2map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:03:00 by ykosaka           #+#    #+#             */
/*   Updated: 2022/12/22 10:26:27 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_lst2map(t_list **lst)
{
	char	**map;
	t_list	*ele;
	size_t	size;
	size_t	i;

	size = ft_lstsize(*lst);
	ele = *lst;
	map = (char **)malloc((size + 1) * sizeof(char *));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		map[i] = ele->content;
		ele = ele->next;
		i++;
	}
	map[i] = NULL;
	ft_lstclear(lst, NULL);
	return (map);
}

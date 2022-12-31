/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:12:29 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 15:27:32 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_lstclear_return_null(t_list **head);
void	ms_lstadd_back_substr(t_list **head, char *line, \
								size_t pos, size_t len);
char	*ms_linkedls_to_str(t_list *head);

void	*ms_lstclear_return_null(t_list **head)
{
	ft_lstclear(head, &free);
	return (NULL);
}

void	ms_lstadd_back_substr(t_list **head, char *line, size_t pos, size_t len)
{
	char	*substr;

	substr = ft_substr(line, pos, len);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(head, ft_lstnew(substr));
	return ;
}

char	*ms_linkedls_to_str(t_list *head)
{
	size_t	joined_str_size;
	char	*joined_str;
	t_list	*cur;

	joined_str_size = 0;
	cur = head;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			joined_str_size += ft_strlen(cur->content);
		cur = cur->next;
	}
	joined_str = ft_calloc(joined_str_size + 1, sizeof(char));
	if (joined_str == NULL)
		exit(EXIT_FAILURE);
	cur = head;
	while (cur != NULL)
	{
		if (cur->content != NULL)
			ft_strlcat(joined_str, cur->content, joined_str_size + 1);
		cur = cur->next;
	}
	return (joined_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_string_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:12:29 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/31 16:21:14 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lexer_string_lstadd_back_substr(t_list **head, char *line, \
			size_t pos, size_t len);
char	*ms_lexer_string_lst_strjoin(t_list *head);

void	ms_lexer_string_lstadd_back_substr(t_list **head, char *line, \
	size_t pos, size_t len)
{
	char	*substr;

	substr = ft_substr(line, pos, len);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(head, ft_lstnew(substr));
	return ;
}

char	*ms_lexer_string_lst_strjoin(t_list *head)
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

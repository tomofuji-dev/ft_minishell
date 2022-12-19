/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/16 15:01:28 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_parser(t_token *token);
void	*clear_cmd_and_return_null(t_cmd *head);
void	free_string_lst(char **lst, size_t size);

t_cmd	*ms_parser(t_token *token)
{
	size_t	idx;
	t_cmd	*head;
	t_cmd	*cur;

	idx = 0;
	head = ms_parser_cmdnew(token, &idx);
	if (head == NULL)
		return (NULL);
	cur = head;
//	while (token[idx++].flag == FLAG_PIPE && token[idx].str)
	while (token[idx++].flag == FLAG_PIPE)
	{
		cur->next = ms_parser_cmdnew(token, &idx);
		if (cur->next != NULL)
			cur->next->prev = cur;
		cur = cur->next;
		if (cur == NULL)
			return (clear_cmd_and_return_null(head));
	}
	return (head);
}

void	*clear_cmd_and_return_null(t_cmd *head)
{
	t_cmd	*cur;

	cur = head;
	while (cur != NULL)
	{
		// free(cur->path);
//		free_string_lst(cur->arg, sizeof(cur->arg) / sizeof(char *));
		free(cur->input);
		free(cur->output);
		cur = cur->next;
	}
	return (NULL);
}

void	free_string_lst(char **lst, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(lst[i++]);
	free(lst);
}

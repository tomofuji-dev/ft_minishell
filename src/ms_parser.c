/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/25 14:22:31 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_parser(t_token *token);
void	*ms_clear_cmd_and_return_null(t_cmd *head);
void	free_string_lst(char **lst);

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
	while (token[idx++].flag == FLAG_PIPE)
	{
		cur->next = ms_parser_cmdnew(token, &idx);
		if (cur->next != NULL)
			cur->next->prev = cur;
		cur = cur->next;
		if (cur == NULL)
			return (ms_clear_cmd_and_return_null(head));
	}
	return (head);
}

void	*ms_clear_cmd_and_return_null(t_cmd *head)
{
	t_cmd	*cur;

	cur = head;
	while (cur != NULL)
	{
		printf("free path\n");
		free(cur->path);
		printf("free arg\n");
		free_string_lst(cur->arg);
		printf("free input\n");
		free(cur->input);
		printf("free output\n");
		free(cur->output);
		cur = cur->next;
	}
	return (NULL);
}

void	free_string_lst(char **lst)
{
	size_t	i;

	i = 0;
	while (lst[i] != NULL)
		free(lst[i++]);
	free(lst);
}

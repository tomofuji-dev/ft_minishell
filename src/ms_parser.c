/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 16:47:31 by tfujiwar         ###   ########.fr       */
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
	head = NULL;
	while (token[idx].str != NULL)
	{
		if (head == NULL)
		{
			head = ms_parser_cmdnew(token, idx);
			cur = head;
		}
		else
		{
			cur->next = ms_parser_cmdnew(token, idx);
			cur = cur->next;
			if (cur->next != NULL)
				cur->next->prev = cur;
		}
		if (cur == NULL)
			return (clear_cmd_and_return_null(head));
		idx++;
	}
}

void	*clear_cmd_and_return_null(t_cmd *head)
{
	t_cmd	*cur;

	cur = head;
	while (cur != NULL)
	{
		free(cur->path);
		free_string_lst(cur->arg, sizeof(cur->arg) / sizeof(char *));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/30 23:28:55 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_parser(t_token *token);
bool	ms_parser_chktokenflag(t_token *token);
void	*ms_clear_cmd_and_return_null(t_cmd *head);
void	free_string_lst(char **lst);

t_cmd	*ms_parser(t_token *token)
{
	size_t	idx;
	t_cmd	*head;
	t_cmd	*cur;

	g_shell.heredoc_sigint = false;
	if (!ms_parser_chktokenflag(token))
		return (print_err_set_status_return_null("syntax error", 2));
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

bool	ms_parser_chktokenflag(t_token *token)
{
	size_t	idx;

	idx = 0;
	if (token[idx].flag == FLAG_PIPE)
		return (false);
	while (token[idx].str != NULL)
	{
		if (token[idx].flag == 0)
			return (false);
		idx++;
	}
	if (idx > 0 && token[idx - 1].flag == FLAG_PIPE)
		return (false);
	return (true);
}

void	*ms_clear_cmd_and_return_null(t_cmd *head)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = head;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->path);
		free_string_lst(cur->arg);
		free(cur->input);
		free(cur->output);
		free(cur);
		cur = next;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_cmdnew_fdsize.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Yoshihiro Kosaka <ykosaka@student.42tok    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:28:00 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/14 14:07:14 by Yoshihiro K      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_parser_cmdnew_fdsize(t_token *token, size_t idx, int flag)
{
	ssize_t	size;

	size = 0;
	while (token[idx] != NULL && token[idx].flag != FLAG_PIPE)
	{
		if (token[idx++].flag & flag == flag)
		{
			if (token[idx++].flag != FLAG_STRING)
				return (SIZE_INVAL);
			size++;
		}
	}
	return (size);
}

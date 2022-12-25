/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:11:38 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/25 14:36:05 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_and_return(void *malloc_obj)
{
	free(malloc_obj);
	return (NULL);
}

void	*print_err_set_status_return_null(char *str, int status)
{
	if (str != NULL)
		ft_putendl_fd(str);
	if (status >= 0)
		g_shell.status = status;
	return (NULL);
}

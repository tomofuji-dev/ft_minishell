/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:03:27 by t.fuji            #+#    #+#             */
/*   Updated: 2022/12/22 11:26:52 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_strlst_count(char *str_lst[])
{
	size_t	count;

	if (str_lst == NULL)
		return (0);
	count = 0;
	while (str_lst[count] != NULL)
		count++;
	return (count);
}

void	ms_strlst_cpy(char **dest, char **src)
{
	size_t	i;

	if (dest == NULL || src == NULL)
		return ;
	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	dest[i] = NULL;
	return ;
}

void	ms_strlst_free(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

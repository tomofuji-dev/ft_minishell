/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t.fuji <t.fuji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:14:42 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/12/21 14:41:39 by t.fuji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*g_shell;
extern char	**environ;

void	init_global(void);
size_t	ms_count_str(char *str_lst[]);
void	ms_strlst_cpy(char **dest, char **src);


void	init_global(void)
{
	size_t	env_count;

	env_count = ms_count_str(environ);
	g_shell->environ = malloc(sizeof(char *) * (env_count + 1));
	if (g_shell->environ == NULL)
		exit(EXIT_FAILURE);
	ms_strlst_cpy(g_shell->environ, environ);
	g_shell->status = 0;
}

size_t	ms_count_str(char *str_lst[])
{
	size_t	count;

	if (str_lst == NULL)
		return (0);
	count = 0;
	while (str_lst[i] != NULL)
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
